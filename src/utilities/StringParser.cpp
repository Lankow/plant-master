/**
 * @file StringParser.cpp
 * @date   2024-06-07
 * @author Lankow
 * @version 1.0
 *
 * @brief This file contains the implementation of the StringParser class.
 *
 * The StringParser class provides static methods for parsing strings to integers
 * and floats, as well as extracting numbers from strings.
 */
#include "utilities/StringParser.hpp"
#include <stdexcept>
#include <cctype>

bool StringParser::parseStringToInt(const std::string &str, int &result)
{
    try
    {
        size_t pos;
        result = std::stoi(str, &pos);
        if (pos != str.length())
        {
            return false;
        }
        return true;
    }
    catch (const std::invalid_argument &)
    {
        return false;
    }
    catch (const std::out_of_range &)
    {
        return false;
    }
}

bool StringParser::parseStringToFloat(const std::string &str, float &result)
{
    try
    {
        size_t pos;
        result = std::stof(str, &pos);
        if (pos != str.length())
        {
            return false;
        }
        return true;
    }
    catch (const std::invalid_argument &)
    {
        return false;
    }
    catch (const std::out_of_range &)
    {
        return false;
    }
}

bool StringParser::extractNumberFromString(const std::string &str, int &result)
{
    std::string numberStr;
    bool numberFound = false;

    for (char ch : str)
    {
        if (std::isdigit(ch))
        {
            numberStr += ch;
            numberFound = true;
        }
        else if (numberFound)
        {
            break;
        }
    }

    if (numberFound)
    {
        try
        {
            result = std::stoi(numberStr);
            return true;
        }
        catch (const std::invalid_argument &)
        {
            return false;
        }
        catch (const std::out_of_range &)
        {
            return false;
        }
    }
    return false;
}