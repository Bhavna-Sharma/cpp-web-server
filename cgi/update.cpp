#include "header.h"

int main (int argc, char* argv[])
{
    std::string request = "";
    getline(std::cin, request);

    if (request != "")
    {
        std::map<std::string, std::string> parsedInput = parseInput(request);
        // form the sql statement
        std::string query = "SELECT * FROM employees WHERE ";
        query += parsedInput["where"];
        query += " = '";
        query += parsedInput["value"];
        query += "';";

        pqxx::result R = executeQuery(query); // execute the query

        // content type header
        std::cout << "Content-type: text/html" << std::endl << std::endl;
        // csv columns header
        std::cout << "employeeid,fullname,homeaddress,emailaddress,salary" << "<br>";
        for (pqxx::const_result_iterator c = R.begin(); c != R.end(); ++c)
        {
            std::cout << c[0].as<int>() << ",";
            std::cout << c[1].as<std::string>() << ",";
            std::cout << c[2].as<std::string>() << ",";
            std::cout << c[3].as<std::string>() << ",";
            std::cout << c[4].as<int>();
        }
    }
    else
    {
        // return an error message if the page is requested alone
        std::cout << "Content-type: text/html" << std::endl << std::endl;
        std::cout << "No request received.";
    }
}
