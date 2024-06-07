/*
 *   StringParser.cpp
 *   ----------------------
 *   Created on: 2024/06/07
 *   Author: Lankow
 */
#include "StringParser.hpp"
#include <stdexcept>

bool StringParser::parseStringToInt(const std::string &str, int &result)
{
    try
    {
        size_t pos;
        result = std::stoi(str, &pos);
        // Check if there are any non-numeric characters after the number
        if (pos != str.length())
        {
            return false;
        }
        return true;
    }
    catch (const std::invalid_argument &)
    {
        // str does not contain a valid number
        return false;
    }
    catch (const std::out_of_range &)
    {
        // str contains a number that is too large for an int
        return false;
    }
}

bool StringParser::parseStringToFloat(const std::string &str, float &result)
{
    try
    {
        size_t pos;
        result = std::stof(str, &pos);
        // Check if there are any non-numeric characters after the number
        if (pos != str.length())
        {
            return false;
        }
        return true;
    }
    catch (const std::invalid_argument &)
    {
        // str does not contain a valid number
        return false;
    }
    catch (const std::out_of_range &)
    {
        // str contains a number that is too large for a float
        return false;
    }
}