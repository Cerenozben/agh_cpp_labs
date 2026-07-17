#pragma once

#include <algorithm>  // std::reverse
#include <cstdint>
#include <vector>  // std::vector

namespace containersVector
{
/****************************************************************/
// Exercise - vectorSize
/**
 * @brief Implement the function 'vectorSize' which return the size of vector.
 * @param v const std::vector<int> & - vector reference
 * @return uint64_t - size of vector
 */
/*********************** place code above ***********************/
/****************************************************************/
uint64_t vectorSize(const std::vector<int> &v);
/****************************************************************/
// Exercise - createVector
/**
 * @brief Implement the template function 'createVector' which create vector with configurable size and default value
 * @param size const uint64_t - size of vector to create
 * @param default_value const T - default value for elements of the vector
 * @return std::vector<T> - created vector
 * @attention T is template type
 */
/*********************** place code above ***********************/
/****************************************************************/
template <typename T>
std::vector<T> createVector(const uint64_t size, const T defaultValue)
{
    return std::vector<T>(size, defaultValue);
}
/****************************************************************/
// Exercise - mergeVectors
/**
 * @brief Implement the template function 'mergeVectors' which concatenate two vectors into one
 * @param v1 const std::vector<T> & - first vector reference
 * @param v2 const std::vector<T> & - second vector reference
 * @return std::vector<T> - merged vector (concatenated v1 and v2 vector)
 * @attention T is template type
 */
/*********************** place code above ***********************/
/****************************************************************/
template <typename T>
std::vector<T> mergeVectors(const std::vector<T> &v1, const std::vector<T> &v2)
{
    std::vector<T> merged = v1;
    merged.insert(merged.end(), v2.begin(), v2.end());
    return merged;
}
/****************************************************************/
// Exercise - vectorReverse
/**
 * @brief implement the function 'vectorReverse' which reverse the elements in vector inplace
 * @param v std::vector<int> & - vector reference
 * @return none
 * @attention Example input: {1, 2, 3} and example output: {3, 2, 1}
 */
/*********************** place code above ***********************/
/****************************************************************/
void vectorReverse(std::vector<int> &v);
/****************************************************************/
// Exercise - vectorFilter
/**
 * @brief implement the function 'vectorFilter' which filter the odd elements in vector inplace
 * @param v std::vector<int> & - vector reference
 * @return none
 * @attention Example input: {1, 2, 3, 4, 5} and example output: {2, 4}
 * @attention Use lambda function and proper functions from algorithms library
 */
/*********************** place code above ***********************/
/****************************************************************/
void vectorFilter(std::vector<int> &v);
/****************************************************************/
// Exercise - vectorRemoveThirdElement
/**
 * @brief implement the function 'vectorRemoveThirdElement' which remove third element of vector inplace
 * @param v std::vector<int> & - vector reference
 * @return none
 * @attention Example input: {1, 2, 3, 4, 5} and example output: {1, 2, 4, 5}
 */
/*********************** place code above ***********************/
/****************************************************************/
void vectorRemoveThirdElement(std::vector<int> &v);
/****************************************************************/
// Exercise - vectorInsertAfterThirdElement
/**
 * @brief implement the function 'vectorInsertAfterThirdElement' which insert new element after third element of vector inplace
 * @param v std::vector<int> & - vector reference
 * @param e int - value to insert after third element of vector v
 * @return none
 * @attention Example input: v = {1, 2, 3, 4, 5}, e = 6 and example output: {1, 2, 3, 6, 4, 5}
 */
/*********************** place code above ***********************/
/****************************************************************/
void vectorInsertAfterThirdElement(std::vector<int> &v, int e);
/****************************************************************/
// Exercise - vectorCountOccurrences
/**
 * @brief implement the template function 'vectorCountOccurrences' which counts how many times the 'value' occurred in the
 * vector
 * @param v const std::vector<T> & - const vector reference
 * @param value const T - value whose number of occurrences should be counted
 * @return uint64_t - counter
 * @attention Example input: v = {1, 2, 2, 3}, value = 2 and example output: 2
 */
/*********************** place code above ***********************/
/****************************************************************/
template <typename T>
uint64_t vectorCountOccurrences(const std::vector<T> &v, const T value)
{
    return static_cast<uint64_t>(std::count(v.begin(), v.end(), value));
}
/****************************************************************/
// Exercise - vectorMean
/**
 * @brief implement the function 'vectorMean' which calculates the mean of elements from the vector of vectors
 * @param vector_of_vectors const std::vector<std::vector<double>> & - vector of vectors reference
 * @return mean - double mean of all elements from vector of vectors
 * @attention Example input: vector_of_vectors = {{1.0, 2.0}, {2.0, 3.0}} and example output: 2.0
 */
/*********************** place code above ***********************/
/****************************************************************/
double vectorMean(const std::vector<std::vector<double>> &vectorOfVectors);
}  // namespace containersVector