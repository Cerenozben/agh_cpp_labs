#pragma once

#include <algorithm>
#include <vector>

namespace templateFunctions
{
/****************************************************************/
// Exercise - templateMax
/**
 * @brief Declare template function "max".
 * Function should returns the greater of two variables of the same type (max function).
 * @param a input value
 * @param b input value
 * @return greater from two inputs
 */
/*********************** place code above ***********************/
/****************************************************************/
template <typename T>
T max(T a, T b)
{
    if (a > b)
    {
        return a;
    }

    return b;
}
/****************************************************************/
// Exercise - templateSortVector
/**
 * @brief Declare template function "templateSortVector".
 * Function should sort in ascending order argument vector.
 * @param values std::vector<T> - values
 * @return none
 */
/*********************** place code above ***********************/
/****************************************************************/
template <typename T>
void templateSortVector(std::vector<T> &values)
{
    std::sort(values.begin(), values.end());
}
}  // namespace templateFunctions