#include <Functions/Recursion.h>

#include <cmath>

namespace recursion
{
/****************************************************************/
// Exercise - gcd
/**
 *
 * @brief Define function "gcd". The greatest common divisor can be computed by Euclid's algorithm:
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
uint32_t gcd(uint32_t a, uint32_t b)
{
    if (b == 0)
    {
        return a;
    }

    return gcd(b, a % b);
}
/****************************************************************/
// Exercise - power
/**
 *
 * @brief Define function "power".
 *  Function should calculate the power of any number using recursion.
 *  x^y
 * @param x uint32_t -  first value
 * @param y uint32_t -  second value
 * @return uint64_t -  x^y
 *
 */
/*********************** place code above ***********************/
/****************************************************************/
uint64_t power(uint32_t x, uint32_t y)
{
    if (y == 0)
    {
        return 1;
    }
    return x * power(x, y - 1);
}
/****************************************************************/
// Exercise - Factorial
/**
 *
 * @brief Define function "findFactorial".
 *  find the Factorial of a number using recursion.
 *
 * @param x uint32_t - input number
 * @return uint64_t - Factorial of number x
 *
 */
/*********************** place code above ***********************/
/****************************************************************/
uint64_t findFactorial(uint32_t n)
{
    if (n == 0 || n == 1)
    {
        return 1;
    }
    return n * findFactorial(n - 1);
}
}  // namespace recursion