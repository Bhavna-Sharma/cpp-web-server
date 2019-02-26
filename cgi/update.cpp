#include "header.h"
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
        query << "UPDATE employees SET ";
        query << "employeeid = '" << parsedInput["employeeid"] << "',";
        query << "fullname = '" << parsedInput["fullname"] << "',";
        query << "homeaddress = '" << parsedInput["homeaddress"] << "',";
        query << "emailaddress = '" << parsedInput["emailaddress"] << "',";
        query << "salary = '" << parsedInput["salary"] << "'";
        query << " WHERE " << parsedInput["where"] << " = '" << parsedInput["value"] << "';";

        pqxx::result R = executeQuery(query.str()); // execute the query

        // content type header
        std::cout << "Content-type: text/html" << std::endl << std::endl;
        // response
        std::cout << "Table has been updated.";
    }
    else
    {
        // return an error message if the page is requested alone
        std::cout << "Content-type: text/html" << std::endl << std::endl;
        std::cout << "No request received.";
    }
}
