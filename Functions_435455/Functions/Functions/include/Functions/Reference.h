#pragma once

#include <string>
#include <vector>

namespace reference
{
/****************************************************************/
// Exercise - toLowerCase
/**
 * @brief Define function "toLowerCase".
 * Function should convert provided string to lowerCase inplace using reference.
 *
 * @param str std::string - string to convert
 * @return none
 */
/*********************** place code above ***********************/
/****************************************************************/
void toLowerCase(std::string &str);
/****************************************************************/
// Exercise - Swap
/**
 * @brief Declare function "swapValues". Function should swap Values of Two arguments Variables.
 * @param a int & -  first value
 * @param b int & -  second value
 * @return none
 */
/*********************** place code above ***********************/
/****************************************************************/
void swapValues(int &a, int &b);
/****************************************************************/
// Exercise - increment
/**
 * @brief Declare function "increment".
 * Function should return incremented argument.
 * Argument should be reference.
 * Argument should be const.
 * @param a int -   value
 * @return int incremented argument
 */
/*********************** place code above ***********************/
/****************************************************************/
int increment(const int &a);
/****************************************************************/
// Exercise - sortVector
/**
 * @brief Declare function "sortVector".
 * Function should sort in ascending order argument vector.
 * @param values std::vector<int> - values
 * @return none
 */
/*********************** place code above ***********************/
/****************************************************************/
void sortVector(std::vector<int> &values);
}  // namespace reference