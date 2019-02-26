#include "header.h"
#include <vector>
#include <sstream>

int main (int argc, char* argv[])
{
    std::string request = "";
    getline(std::cin, request);

    if (request != "")
    {
        std::map<std::string, std::string> parsedInput = parseInput(request);

        // form the sql statement
        std::stringstream query;
        query << "INSERT INTO employees (employeeid, fullname, homeaddress, emailaddress, salary) VALUES (";
        query << "'" << parsedInput["employeeid"] << "',";
        query << "'" << parsedInput["fullname"] << "',";
        query << "'" << parsedInput["homeaddress"] << "',";
        query << "'" << parsedInput["emailaddress"] << "',";
        query << "'" << parsedInput["salary"] << "'";
        query << ");";

        pqxx::result R = executeQuery(query.str()); // execute the query

        // content type header
        std::cout << "Content-type: text/html" << std::endl << std::endl;
        // output
        std::cout << "Table has been updated.";
    }
    else
    {
        // return an error message if the page is requested alone
        std::cout << "Content-type: text/html" << std::endl << std::endl;
        std::cout << "No request received.";
    }
}
