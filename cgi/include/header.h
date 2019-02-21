#include <iostream>

#include <spdlog/spdlog.h>
#include <spdlog/logger.h>
#include <spdlog/sinks/base_sink.h>
#include <pqxx/pqxx>

// initialize the logger
auto logger = spdlog::basic_logger_mt("basic_logger", "../logs/cgi-log.txt");

pqxx::result executeQuery (std::string query)
{
    try {
        pqxx::connection C("dbname=cpp-web-server user=cgi password=password hostaddr=127.0.0.1 port=5432");
        if (!C.is_open())
        {
            logger->warn("Could not connect to database");
        }

        // create and execute sql statement
        pqxx::nontransaction N(C);
        pqxx::result R = N.exec(query);
        
        C.disconnect(); // disconnect from database

        return R; // return the result object

    } catch (const std::exception &e) {
        logger->warn("Error in database connection:");
        logger->warn(e.what());
    }
}

std::map<std::string, std::string> parseInput (std::string inputString)
{
    std::map<std::string, std::string> parameters;
    std::string key = "";
    std::string value = "";
    int part = 0; // 0 is key and 1 is value
    char c;

    for (int i = 0; i < inputString.length(); i++)
    {
        c = inputString.at(i);
        if (c == '=')
        {
            part = 1;
        }
        else if (c == '&')
        {
            parameters[key] = value;
            key = "";
            value = "";
            part = 0;
        }
        else
        {
            if (part == 0)
            {
                key += c;
            }
            else if (part == 1)
            {
                value += c;
            }
        }
    }
}