#pragma once

#include <cstdint>
namespace recursion
{
/****************************************************************/
// Exercise - gcd
/**
 *
 * @brief Declare function "gcd".
 *  The greatest common divisor can be computed by Euclid's algorithm:
 *  gcd(a, 0) = a
 *  gcd(a, b) = gcd(b, a mod b)
 *  Write a function that computes gcd(), assuming the parameters and the result are of type uint32_t.
 *
 * @param a uint32_t -  first value
 * @param b uint32_t -  second value
 * @return uint32_t -  The greatest common divisor
 *
 */
/*********************** place code above ***********************/
/****************************************************************/
uint32_t gcd(uint32_t a, uint32_t b);
/****************************************************************/
// Exercise - power
/**
 *
 * @brief Declare function "power".
 *  Function should calculate the power of any number using recursion.
 *  x^y
 * @param x uint32_t -  first value
 * @param y uint32_t -  second value
 * @return  uint64_t  -  x^y
 *
 */
/*********************** place code above ***********************/
/****************************************************************/
uint64_t power(uint32_t x, uint32_t y);
/****************************************************************/
// Exercise - Factorial
/**
 *
 * @brief Declare function "findFactorial".
 *  find the Factorial of a number using recursion.
 *
 * @param n uint32_t - input number
 * @return uint64_t - Factorial of number n
 *
 */
/*********************** place code above ***********************/
/****************************************************************/
uint64_t findFactorial(uint32_t n);
}  // namespace recursion