#include <Containers/ContainerSet.h>

#include <numeric>

namespace containersSet
{
/****************************************************************/
// Exercise - setSize
/**
 * @brief Implement the function 'setSize' which return the size of set.
 * @param s const std::set<int> & - set reference
 * @return unsigned long - size of set
 */
/*********************** place code above ***********************/
/****************************************************************/
uint64_t setSize(const std::set<int> &s)
{
    return s.size();
}
/****************************************************************/
// Exercise - countSumOfUniqueElements
/**
 * @brief Implement the function 'countSumOfUniqueElements' which count the sum of unique elements in vector
 * @param v const std::vector<double> & - vector reference
 * @return double - sum of unique elements
 */
/*********************** place code above ***********************/
/****************************************************************/
double countSumOfUniqueElements(const std::vector<double> &v)
{
    std::set<double> uniqueElements(v.begin(), v.end());
    double sum = 0.0;
    for (double element : uniqueElements)
    {
        sum += element;
    }
    return sum;
}
}  // namespace containersSet