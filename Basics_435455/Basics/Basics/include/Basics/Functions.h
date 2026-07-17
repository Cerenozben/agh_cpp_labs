#pragma once

#include <array>
#include <cstdint>

namespace basics
{
/**
 * @brief Write function 'mean' which return mean value of array 'numbers'
 * @param numbers - std::array of 3 doubles
 * @return double - mean value
 *
 */
// student code begin
double mean(std::array<double,3>numbers);
// student code end

/**
 * @brief Write function 'celsiusToFahrenheit' which convert Celsius (C) to Fahrenheit (F)
 * @param celsius - double Celsius degrees
 * @return double - Fahrenheit degrees
 * @attention Formula: F = C * (9 / 5) + 32
 *
 */
// student code begin
double celsiusToFahrenheit(double celsius);
// student code end

/**
 * @brief Write function 'findMax' which returns the maximum value from array 'numbers'
 * @param numbers - std::array of 3 doubles
 * @return double - maximum value
 *
 */
// student code begin
double findMax(std::array<double,3>numbers);
// student code end

/**
 * @brief Write function 'calculateCircleArea' which calculates the area of a circle
 * @param radius - double radius of the circle
 * @return double - area of the circle
 * @attention use std::numbers::pi
 *
 */
// student code begin
double calculateCircleArea(double radius);
// student code end

/**
 * @brief Write function 'isPalindrome' which checks if a number reads the same forwards and backwards
 * @param number - uint32_t number to check
 * @return bool - true if palindrome, false otherwise
 * @attention Example: 121 is a palindrome, 123 is not
 *
 */
// student code begin
bool isPalindrome(uint32_t number);
// student code end

}  // namespace basics