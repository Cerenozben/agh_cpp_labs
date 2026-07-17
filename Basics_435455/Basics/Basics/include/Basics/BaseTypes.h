#pragma once

#include <cstdint>
namespace basics
{

/**
 * @brief Return true if both 'a' and 'b' are equal to true, false otherwise.
 *
 */
bool boolExercise1(bool a, bool b);

/**
 * @brief Return true only if only one of the 'a' and 'b' values is equal to true.
 *
 */
bool boolExercise2(bool a, bool b);

/**
 * @brief Return true only if the 'a' or 'b' value is equal to true.
 *
 */
bool boolExercise3(bool a, bool b);

/**
 * @brief Return true if 'a' is false, and false if 'a' is true (logical not).
 *
 */
bool boolExercise4(bool a);

/**
 * @brief Increment 'arg' and return incremented value.
 *
 */
int16_t shortExercise1(int16_t arg);

/**
 * @brief Print on console value of 'arg'.
 *
 */
void intExercise1(int arg);

/**
 * @brief Return true if 'arg' value is greater than or equal to 10, return false otherwise.
 *
 */
bool intExercise2(int arg);

/**
 * @brief Calculate the sum of 'a' and 'b' and assign result to value 'sum'. Return 'sum'.
 *
 */
unsigned int uintExercise1(unsigned int a, unsigned int b);

/**
 * @brief Return the minimal value of 'a' and 'b'.
 *
 */
unsigned int uintExercise2(unsigned int a, unsigned int b);

/**
 * @brief Return the multiplication of values 'a' and 'b'.
 *
 */
float floatExercise1(float a, float b);

/**
 * @brief Return the maximum absolute value from values 'a' and 'b'.
 *
 */
double doubleExercise1(double a, double b);

/**
 * @brief Return true if 'a' plus 'b' are equal to 'c', false otherwise.
 * @warning https://www.geeksforgeeks.org/cpp/compare-float-and-double-while-accounting-for-precision-loss/
 */
bool doubleExercise2(double a, double b, double c);

}  // namespace basics