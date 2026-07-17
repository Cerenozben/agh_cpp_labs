#include <Functions/Overload.h>

#include <cmath>
#include <iomanip>
#include <iostream>

namespace overload
{
/****************************************************************/
// Exercise - add function overload
/**
 * @brief Define multiple functions "add".
 * Functions should add two or three numbers of type int.
 * @param a  input a
 * @param b  input b
 * @param c  input c
 * @return none
 */

/*********************** place code above ***********************/
/****************************************************************/
int add(int &a, int &b)
{
    return a + b;
}
int add(int &a, int &b, int &c)
{
    return a + b + c;
}
/****************************************************************/
// Exercise - round function overload
/**
 * @brief Define multiple functions "round".
 * Functions should round argument values and print rounded value on console.
 * Order of magnitude of rounding should be depend on argument type.
 * For argument of type double the order of magnitude of rounding should be 10^2.
 * For argument of type float the order of magnitude of rounding should be 10^3.
 * For argument of type int the order of magnitude of rounding should be 10^4.
 * @param value  input value
 * @return none
 */
/*********************** place code above ***********************/
/****************************************************************/
void round(double value)
{
    double rounded = std::round(value / 100.0) * 100.0;
    std::cout << rounded << '\n';
}
void round(float value)
{
    float rounded = std::round(value / 1000.0F) * 1000.0F;
    std::cout << rounded << '\n';
}
void round(int value)
{
    int rounded = static_cast<int>(std::round(value / 10000) * 10000);
    std::cout << rounded << '\n';
}
/****************************************************************/
// Exercise - precisionPrint function overload
/**
 * @brief Define multiple functions "precisionPrint".
 * Functions should print on console floating type numbers with precision depending on argument type.
 * For argument of type float precision should be 2 decimal places.
 * For argument of type double precision should be 4 decimal places.
 * For argument of type long double precision should be 6 decimal places.
 * @param value  input value
 * @return none
 */
/*********************** place code above ***********************/
/****************************************************************/
void precisionPrint(float value)
{
    std::cout << std::setprecision(2) << value << '\n';
}
void precisionPrint(double value)
{
    std::cout << std::setprecision(4) << value << '\n';
}
void precisionPrint(long double value)
{
    std::cout << std::setprecision(6) << value << '\n';
}
/****************************************************************/
// Exercise - polynomialPrint function overload
/**
 * @brief Define multiple functions "polynomialPrint".
 * Functions should print on console the polynomial formula. "f(x) = n0 + n1*x^1 + n2*x^2"
 * For argument should be floats.
 * Function should have one, two or three arguments.
 * @param n0 multiplier on 0 power of x
 * @param n1 multiplier on 1 power of x
 * @param n2 multiplier on 2 power of x
 * @return none
 */
/*********************** place code above ***********************/
/****************************************************************/
void polynomialPrint(float n0)
{
    std::cout << "f(x) = " << n0 << '\n';
}
void polynomialPrint(float n0, float n1)
{
    std::cout << "f(x) = " << n0 << "+" << n1 << "*x^1 \n";
}
void polynomialPrint(float n0, float n1, float n2)
{
    std::cout << "f(x) = " << n0 << "+" << n1 << "*x^1 +" << n2 << "*x^2 \n";
}
}  // namespace overload