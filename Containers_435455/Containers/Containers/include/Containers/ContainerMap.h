#pragma once

#include <cstdint>  // uint32_t, uint64_t, etc.
#include <map>      // std::map
#include <string>   // std::string
#include <utility>  // std::pair

namespace containersMap
{
/****************************************************************/
// Exercise - mapSize
/**
 * @brief Implement the function 'mapSize' which return the size of map.
 * @param m const std::map<std::string, int> & - map reference
 * @return unsigned long - size of map
 */
/*********************** place code above ***********************/
/****************************************************************/
uint64_t mapSize(const std::map<std::string, int> &m);
/****************************************************************/
// Exercise - mapClear
/**
 * @brief Implement the template function 'mapClear' which clear the content of map (remove all elements)
 * @param m map to clear
 * @return none
 */
/*********************** place code above ***********************/
/****************************************************************/
template <typename Key, typename Value>
void mapClear(std::map<Key, Value> &m)
{
    m.clear();
}
/****************************************************************/
// Exercise - mapAdd
/**
 * @brief Implement the template function 'mapAdd' which add one element to map
 * @param m the map to which the item should be added
 * @param x element (pair key, value) to be added - should be const
 * @return none
 */
/*********************** place code above ***********************/
/****************************************************************/
template <typename Key, typename Value>
void mapAdd(std::map<Key, Value> &m, const std::pair<Key, Value> x)
{
    m.insert(x);
}
/****************************************************************/
// Exercise - mapGet
/**
 * @brief Implement the template function 'mapGet' which return element from map for the specified key
 * @param m the map from which the item should be returned
 * @param k the specified key - should be const
 * @return value at specified key
 */
/*********************** place code above ***********************/
/****************************************************************/
template <typename Key, typename Value>
Value mapGet(std::map<Key, Value> &m, const Key key)
{
    return m.at(key);
}
/****************************************************************/
// Exercise - mapReplace
/**
 * @brief Implement the template function 'mapReplace' which replace element in map at the specified key
 * @param m the map where the item should be replaced
 * @param k the specified key - should be const
 * @param v new value - should be const
 * @return none
 */
/*********************** place code above ***********************/
/****************************************************************/
template <typename Key, typename Value>
void mapReplace(std::map<Key, Value> &m, const Key &k, const Value &v)
{
    m[k] = v;
}
/****************************************************************/
// Exercise - mapMerge
/**
 * @brief Implement the template function 'mapMerge' which merge two maps into one
 * @param m1 first map to merge - should be const
 * @param m2 second map to merge - should be const
 * @attention For the keys which exists both in m1 and m2 - the values from m2 should have higher priority
 * @return merged map
 */
/*********************** place code above ***********************/
/****************************************************************/
template <typename Key, typename Value>
std::map<Key, Value> mapMerge(const std::map<Key, Value> &m1, const std::map<Key, Value> &m2)
{
    std::map<Key, Value> mergedMap = m1;
    for (const auto &item : m2)
    {
        mergedMap[item.first] = item.second;
    }
    return mergedMap;
}
}  // namespace containersMap