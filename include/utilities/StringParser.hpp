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

/**
 * @class StringParser
 * @brief A utility class for parsing strings into numeric values.
 *
 * The StringParser class provides methods to parse strings into integers and floats,
 * as well as extract numeric values from strings.
 */
class StringParser
{
public:
    /**
     * @brief Parses a string into an integer.
     *
     * This method attempts to parse the entire input string into an integer.
     *
     * @param str The string to be parsed.
     * @param result The integer result of the parsing, if successful.
     * @return true if the string was successfully parsed into an integer, false otherwise.
     */
    static bool parseStringToInt(const std::string &str, int &result);

    /**
     * @brief Parses a string into a float.
     *
     * This method attempts to parse the entire input string into a float.
     *
     * @param str The string to be parsed.
     * @param result The float result of the parsing, if successful.
     * @return true if the string was successfully parsed into a float, false otherwise.
     */
    static bool parseStringToFloat(const std::string &str, float &result);

    /**
     * @brief Extracts the first number found in a string.
     *
     * This method scans the input string for the first sequence of digits and
     * attempts to parse it into an integer.
     *
     * @param str The string to be scanned.
     * @param result The integer result of the extraction, if successful.
     * @return true if a number was successfully extracted from the string, false otherwise.
     */
    static bool extractNumberFromString(const std::string &str, int &result);
};

#endif // STRING_PARSER_HPP