#pragma once

#include <string>
namespace basics
{
/****************************************************************/
// Exercise - convert2Ascii
/**
 * @brief Declare function "convert2Ascii". Function should convert character into unsigned int value in ascii code.
 * https://www.asciitable.com/
 * @param character char -  character to convert
 * @return unsigned int - character ascii code
 *
 */
/*********************** place code above ***********************/
/****************************************************************/
unsigned int convert2Ascii(char character);
/****************************************************************/
// Exercise - HexPrint
/**
 * @brief Declare function "hexPrint". Function should print string in ascii hex dump form (ascii hex values of character with
 * space between each value ).
 * @param inputString const std::string & -  first value
 * @return none
 */
/*********************** place code above ***********************/
/****************************************************************/
void hexPrint(const std::string &inputString);
/****************************************************************/
// Exercise - defaultValues
/**
 * @brief Declare function "defaultValues".
 * Function should print argument values on console.
 * Function should have 4 arguments of std::string type.
 * 3 arguments of this function should have default values "empty row number #" where "#" is number of argument.
 * Each value should be printed in separate row.
 * @param arg0 const std::string &
 * @param arg1 const std::string &
 * @param arg2 const std::string &
 * @param arg3 const std::string &
 * @return none
 */
/*********************** place code above ***********************/
/****************************************************************/
void defaultValues(const std::string &arg0,
                   const std::string &arg1 = "empty row number 1",
                   const std::string &arg2 = "empty row number 2",
                   const std::string &arg3 = "empty row number 3");
/****************************************************************/
// Exercise - min
/**
 * @brief Declare function "min".
 * Function should returns the smaller of two float.
 * @param a input value
 * @param b input value
 * @return smaller from two inputs
 */
/*********************** place code above ***********************/
/****************************************************************/
template <typename T>
T min(T a, T b);
}  // namespace basics