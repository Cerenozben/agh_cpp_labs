#pragma once

#include <array>
#include <cstdint>
#include <string>
#include <utility>

namespace basics
{
/**
 * @brief return sum of all odd numbers in range from 0 do 50
 *
 */
int forExercise1();

/**
 * @brief Convert two list 'names', 'surnames' into one list of pairs <name, surname> and return this list
 *
 */
std::array<std::pair<std::string, std::string>, 2> forExercise2(std::array<std::string, 2> names,
                                                                std::array<std::string, 2> surnames);

/**
 * @brief Calculate and return the factorial of 'n'
 *
 */
uint32_t forExercise3(uint32_t n);

/**
 * @brief Count the number of leading zero bits in 'value' (starting from the most significant bit).
 * For example: value=0b00001010 (8-bit) returns 4, value=0b10000000 returns 0
 * Similar to https://en.cppreference.com/w/cpp/numeric/countl_zero.html
 *
 */
uint8_t forExercise4(uint8_t value);

/**
 * @brief Iterate over elements in a given 'numbers' array until the sum of elements does not exceed 100.
 * Return the number of required iterations.
 *
 */
int whileExercise1(std::array<int, 10> numbers);

/**
 * @brief Find the first exponent where 'base' raised to that power exceeds 'limit'.
 * For example: base=2, limit=1000 returns 10 (because 2^10=1024 > 1000, but 2^9=512 <= 1000)
 *
 */
uint32_t whileExercise2(uint32_t base, uint32_t limit);

}  // namespace basics