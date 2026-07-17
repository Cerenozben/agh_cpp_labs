#pragma once

namespace basics
{
/**
 * @brief Print on console value of 'arg' in decimal form if 'arg' is greater than 100
 *
 */
void ifExercise1(int arg);

/**
 * @brief Return true if 'arg' is greater than 100, false otherwise
 *
 */
bool ifElseExercise1(int arg);

/**
 * @brief Return -1 if 'arg' value is negative, return 0 if 'arg' value is equal to 0 and return 1 if 'arg' value is positive
 *
 */
int ifElseIfElseExercise1(int arg);

/**
 * @brief Implement simple calculator using switch ... case statement
 * Arithmetic operators to support: *, +, -, /
 * Return the result of the equation with the specified arithmetic operator
 * When the operator is not supported, the 0.0 value should be returned.
 * @attention a = 2 | b = 3 | arithmetic_operator = '*' -> Result = a * b = 6
 * @attention a = 2 | b = 4 | arithmetic_operator = '/' -> Result = a / b = 0.5
 *
 */
float switchCaseExercise1(float a, char arithmeticOperator, float b);

/**
 * @brief Return -1 if 'arg' value is odd, and 1 if value is even. Use ternary operator.
 *
 */
int ternaryOperatorExercise1(unsigned int arg);

}  // namespace basics