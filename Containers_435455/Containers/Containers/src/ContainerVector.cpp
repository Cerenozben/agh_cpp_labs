#include <Containers/ContainerVector.h>

#include <algorithm>
#include <cstdint>
#include <numeric>

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
uint64_t vectorSize(const std::vector<int> &v)
{
    return v.size();
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
void vectorReverse(std::vector<int> &v)
{
    std::ranges::reverse(v);
}
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
void vectorFilter(std::vector<int> &v)
{
    v.erase(std::ranges::remove_if(v, [](int x) { return x % 2 != 0; }).begin(), v.end());
}
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
void vectorRemoveThirdElement(std::vector<int> &v)
{
    v.erase(v.begin() + 2);
}
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
void vectorInsertAfterThirdElement(std::vector<int> &v, int e)
{
    v.insert(v.begin() + 3, e);
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
double vectorMean(const std::vector<std::vector<double>> &vectorOfVectors)
{
    double sum = 0.0;
    int count = 0;

    for (const auto &innerVector : vectorOfVectors)
    {
        for (double val : innerVector)
        {
            sum += val;
            count++;
        }
    }
    return sum / count;
}
}  // namespace containersVector