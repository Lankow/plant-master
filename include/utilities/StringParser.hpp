/**
 * @file StringParser.hpp
 * @date   2024-06-07
 * @author Lankow
 * @version 1.0
 *
 * @brief This file contains the definition of the StringParser class.
 *
 * The StringParser class provides static methods for parsing strings to integers
 * and floats, as well as extracting numbers from strings.
 */
#ifndef STRING_PARSER_HPP
#define STRING_PARSER_HPP

#include <string>

class StringParser
{
public:
    static bool parseStringToInt(const std::string &str, int &result);
    static bool parseStringToFloat(const std::string &str, float &result);
    static bool extractNumberFromString(const std::string &str, int &result);
};

#endif // STRING_PARSER_HPP