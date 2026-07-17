#pragma once

#include <algorithm>  // std::reverse
#include <cstdint>
#include <set>     // std::set
#include <vector>  // std::vector

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
uint64_t setSize(const std::set<int> &s);
/****************************************************************/
// Exercise - setClear
/**
 * @brief Implement the template function 'setClear' which clear the content of set (remove all elements)
 * @param s set to clear
 * @return none
 */
/*********************** place code above ***********************/
/****************************************************************/
template <typename T>
void setClear(std::set<T> &s)
{
    s.clear();
}
/****************************************************************/
// Exercise - setAdd
/**
 * @brief Implement the template function 'setAdd' which add one element to set
 * @param s the set to which the item should be added
 * @param x element to be added - should be const
 * @return none
 */
/*********************** place code above ***********************/
/****************************************************************/
template <typename T>
void setAdd(std::set<T> &s, const T x)
{
    s.insert(x);
}
/****************************************************************/
// Exercise - setSwap
/**
 * @brief Implement the template function 'setSwap' which swap the content of two sets
 * @param s1 - first set
 * @param s2 - second set
 * @return none
 */
/*********************** place code above ***********************/
/****************************************************************/
template <typename T>
void setSwap(std::set<T> &s1, std::set<T> &s2)
{
    s1.swap(s2);
}
/****************************************************************/
// Exercise - toSet
/**
 * @brief Implement the template function 'toSet' which convert vector to set
 * @param v const std::vector<T> & - vector reference
 * @return std::set<T> - created set
 * @attention T is template type
 */
/*********************** place code above ***********************/
/****************************************************************/
template <typename T>
std::set<T> toSet(const std::vector<T> &v)
{
    return std::set<T>(v.begin(), v.end());
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
double countSumOfUniqueElements(const std::vector<double> &v);
/****************************************************************/
// Exercise - setIntersection
/**
 * @brief Implement the function 'setIntersection' which takes two sets and return the intersection of them (elements that
 * exists in both sets)
 * @param s1 const std::set<T> & first set
 * @param s2 const std::set<T> & second set
 * @return std::set<T> - s1 & s2 intersection
 */
/*********************** place code above ***********************/
/****************************************************************/
template <typename T>
std::set<T> setIntersection(const std::set<T> &s1, const std::set<T> &s2)
{
    std::set<T> result;

    for (const T &element : s1)
    {
        if (s2.find(element) != s2.end())
        {
            result.insert(element);
        }
    }
    return result;
}
}  // namespace containersSet