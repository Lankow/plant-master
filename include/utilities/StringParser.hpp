/*
 *   StringParser.hpp
 *   ----------------------
 *   Created on: 2024/06/07
 *   Author: Lankow
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