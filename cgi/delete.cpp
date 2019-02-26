#include "header.h"

int main (int argc, char* argv[])
{
    std::string request = "";
    getline(std::cin, request);

    if (request != "")
    {
        std::map<std::string, std::string> parsedInput = parseInput(request);
        // form the sql statement
        std::string query = "DELETE FROM employees WHERE ";
        query += parsedInput["where"];
        query += " = '";
        query += parsedInput["value"];
        query += "';";

        pqxx::result R = executeQuery(query); // execute the query

        // content type header
        std::cout << "Content-type: text/html" << std::endl << std::endl;
        // output message
        std::cout << "Table has been updated.";
    }
    else
    {
        // return an error message if the page is requested alone
        std::cout << "Content-type: text/html" << std::endl << std::endl;
        std::cout << "No request received.";
    }
}
