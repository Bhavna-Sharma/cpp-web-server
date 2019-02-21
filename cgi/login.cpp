#include <iostream>
#include <sstream>

#include <spdlog/spdlog.h>
#include <spdlog/logger.h>
#include <spdlog/sinks/base_sink.h>

#include <json.hpp>
using json = nlohmann::json; // for convenience

#include <pqxx/pqxx>

#include <cryptopp/cryptlib.h>
#include <cryptopp/hex.h>
#include <cryptopp/files.h>
#include <cryptopp/sha.h>

// initialize the logger
auto logger = spdlog::basic_logger_mt("basic_logger", "../logs/cgi-log.txt");

std::string hash (std::string* password)
{
    // create a hex encoder to output to the stringstream
    std::stringstream hashOutput;
    CryptoPP::HexEncoder encoder(new CryptoPP::FileSink(hashOutput));

    std::string digest; // will be the result of the hashing

    CryptoPP::SHA256 hash;
    hash.Update((const byte*)password->data(), password->size());
    digest.resize(hash.DigestSize()); // resize the string for the new data
    hash.Final((byte*)&digest[0]);

    // output the final string
    CryptoPP::StringSource(digest, true, new CryptoPP::Redirector(encoder));
    return hashOutput.str();
}

int checkPassword (std::string* username, std::string* password)
{
    std::string attemptedHash = hash(password);
    std::string storedHash;

    try {
        pqxx::connection C("dbname=project-manager user=cgi password=password hostaddr=127.0.0.1 port=5432");
        if (!C.is_open())
        {
            logger->warn("login.cpp could not connect to database");
            return 2; // database connection error
        }

        // create and execute sql statement
        std::stringstream sql;
        sql << "SELECT hash FROM users WHERE username = '" << *username << "';";
        pqxx::nontransaction N(C);
        pqxx::result R = N.exec(sql.str());

        logger->info(attemptedHash);

        // get first value from sql result
        for (pqxx::const_result_iterator row = R.begin(); row != R.end(); ++row)
        {
            storedHash = row[0].as<std::string>();
        }
        
        C.disconnect(); // disconnect from database

        if (attemptedHash == storedHash)
        {
            return 0; // correct password
        }
        else
        {
            return 1; // incorrect password
        }

    } catch (const std::exception &e) {
        logger->warn("Error in login.cpp checkPassword():");
        logger->warn(e.what());
        return 2; // database connection error
    }
}

std::string createSession (std::string* username)
{
    // create session id
    std::string session = "";
    for (int i = 0; i < 64; i++)
    {
        session += std::to_string(rand() % 9);
    }

    try {
        pqxx::connection C("dbname=project-manager user=cgi password=password hostaddr=127.0.0.1 port=5432");
        if (!C.is_open())
        {
            // connection error
            logger->warn("login.cpp could not connect to database");
        }

        // create and execute sql statement
        std::stringstream sql;
        sql << "UPDATE users SET session = '" << session << "' WHERE username = '" << *username << "';";
        pqxx::nontransaction N(C);
        N.exec(sql.str()); // no need to get result

        C.disconnect(); // disconnect from database
        return session;

    } catch (const std::exception &e) {
        logger->warn("Error in login.cpp createSession():");
        logger->warn(e.what());
    }
}

int main (int argc, char* argv[])
{
    std::string request;
    getline(std::cin, request);

    std::string username = "elan";
    std::string password = "password";

    if (request != "")
    {
        int validation = checkPassword(&username, &password);
        json response;
        if (validation == 1)
        {
            std::string session = createSession(&username);
            response["username"] = username;
            response["session"] = session;
        }
        std::cout << "Content-type: application/json" << std::endl << std::endl;
        std::cout << response.dump() << std::endl; // output the json
    }
    else
    {
        // return an error message if the page is requested alone
        std::cout << "Content-type: text/html" << std::endl << std::endl;
        std::cout << "No request received." << std::endl;
    }
}
