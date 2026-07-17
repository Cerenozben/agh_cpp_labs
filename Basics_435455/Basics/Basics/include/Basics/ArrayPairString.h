#pragma once

#include <array>
#include <string>
#include <utility>

namespace basics
{
/**
 * @brief Create and return the pair created from the 'first' and 'second' values.
 *
 */
std::pair<double, bool> pairExercise1(double first, bool second);

/**
 * @brief Create pair of bools.
 * @attention the first value of the pair should indicate if the number is higher than 0.
 * @attention the second value of the pair should indicate if the number is even.
 *
 */
std::pair<bool, bool> pairExercise2(int number);

/**
 * @brief Create pair with swapped values from pair 'to_swap'.
 * @attention First -> Second && Second -> First
 *
 */
std::pair<double, int> pairExercise3(std::pair<int, double> toSwap);

/**
 * @brief Create and return std::array of integers with following numbers: 1, 2, 3
 *
 */
std::array<int, 3> arrayExercise1();

/**
 * @brief Return the second element of array 'arg'.
 *
 */
int arrayExercise2(std::array<int, 3> arg);

/**
 * @brief Return the sum of the first and the last elements of array 'arg'.
 * @attention use front and back methods of std::array container.
 *
 */
int arrayExercise3(std::array<int, 3> arg);

/**
 * @brief Check if array 'a' is a contiguous subarray of array 'b'.
 * For example: {1, 2, 3} is subarray of {0, 1, 2, 3, 4}, but {1, 3, 4} is not subarray of {0, 1, 2, 3, 4}.
 * Similar to substring check for strings.
 */
bool arrayExercise4(const std::array<int, 3> &a, const std::array<int, 5> &b);

/**
 * @brief Return the size of string 'arg'.
 *
 */
int stringExercise1(const std::string &arg);

/**
 * @brief Return concatenated string (merge 'a' and 'b' strings into one string).
 *
 */
std::string stringExercise2(const std::string &a, const std::string &b);

/**
 * @brief Replace the first character in the string 'a' with 'Hello' and return the modified string.
 * @attention Use replace method.
 *
 */
std::string stringExercise3(std::string arg);

/**
 * @brief Check if string 'substring' is contained within string 'str'.
 * For example: "world" is substring of "Hello world", but "word" is not substring of "Hello world".
 * @attention Use find method of std::string.
 */
bool stringExercise4(const std::string &str, const std::string &substring);

/**
 * @brief Convert all characters in string 'arg' to uppercase and return the result.
 * @attention Use loop and ::toupper function from <cctype>.
 */
std::string stringExercise5(std::string arg);

/**
 * @brief Count the number of occurrences of character 'c' in string 'str'.
 * @attention Use loop to iterate through the string.
 */
int stringExercise6(const std::string &str, char c);

/**
 * @brief Return the substring starting at position 'pos' with length 'len'.
 * For example: "Hello world" with pos=6, len=5 returns "world"
 * @attention Use substr method.
 */
std::string stringExercise7(const std::string &str, size_t pos, size_t len);

/**
 * @brief Check if string 'str' starts with string 'prefix'.
 * For example: "Hello world" starts with "Hello" but not with "world"
 * @attention Use compare method or substr.
 */
bool stringExercise8(const std::string &str, const std::string &prefix);

}  // namespace basics