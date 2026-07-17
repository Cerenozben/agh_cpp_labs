#include <Containers/ContainerMap.h>

#include <cstdint>

namespace containersMap
{
/****************************************************************/
// Exercise - mapSize
/**
 * @brief Implement the function 'mapSize' which return the size of map.
 * @param m const std::map<int> & - map reference
 * @return unsigned long - size of map
 */
/*********************** place code above ***********************/
/****************************************************************/
uint64_t mapSize(const std::map<std::string, int> &m)
{
    return m.size();
}
}  // namespace containersMap