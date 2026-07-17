#include <Functions/Basic.h>

#include <cmath>
#include <cstdint>
#include <iostream>
#include <string>

namespace basics
{
/****************************************************************/
// Exercise - convert2Ascii
/**
 * @brief Declare function "convert2Ascii". Function should convert character into unsigned int value in ascii code.
 * https://www.asciitable.com/
 *
 * @param character char -  character to convert
 * @return unsigned int - character ascii code
 *
 */
/*********************** place code above ***********************/
/****************************************************************/
namespace
{
unsigned int convert2Ascii(char character)
{
    return static_cast<unsigned int>(character);
}
}  // namespace
/****************************************************************/
// Exercise - HexPrint
/**
 * @brief Define function "hexPrint". Function should print string in ascii hex dump form (ascii hex values of character with
 * space between each value ).
 *
 * @param inputString const std::string & -  first value
 * @return none
 */
/*********************** place code above ***********************/
/****************************************************************/
namespace
{
void hexPrint(const std::string &inputString)
{
    for (char c : inputString)
    {
        std::cout << std::hex << static_cast<unsigned int>(static_cast<unsigned char>(c)) << " ";
    }
    std::cout << std::dec << '\n';
}
}  // namespace
/****************************************************************/
// Exercise - defaultValues
/**
 * @brief Define function "defaultValues".
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
namespace
{
void defaultValues(const std::string &arg0,
                   const std::string &arg1 = "empty row number 1",
                   const std::string &arg2 = "empty row number 2",
                   const std::string &arg3 = "empty row number 3")
{
    std::cout << arg0 << '\n';
    std::cout << arg1 << '\n';
    std::cout << arg2 << '\n';
    std::cout << arg3 << '\n';
}
}  // namespace
/****************************************************************/
// Exercise - min
/**
 * @brief Define template function "min".
 * Function should returns the smaller of two float.
 * @param a input value
 * @param b input value
 * @return smaller from two inputs
 */
/*********************** place code above ***********************/
/****************************************************************/
namespace
{
template <typename T>
T min(T a, T b)
{
    return (a < b) ? a : b;
}
}  // namespace
}  // namespace basics