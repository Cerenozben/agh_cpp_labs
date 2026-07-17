# AdvanceStructures

**All classes/structures enumerators shall be implemented in advanceStructures namespace.**

## Useful links

- [https://en.cppreference.com/w/cpp/utility/hash/operator()]
- [https://en.cppreference.com/w/cpp/algorithm/find]
- [https://en.cppreference.com/w/cpp/algorithm/sort]
- [https://www.geeksforgeeks.org/bitwise-operators-in-c-cpp/]
- [https://www.geeksforgeeks.org/how-to-overload-less-than-operator-in-cpp/]
- [https://en.cppreference.com/w/cpp/language/operator_comparison]

## **Addresses**

Implementation shall be placed in [Addresses.hpp](../AdvanceStructures/include/AdvanceStructures/Addresses.hpp)

### Tasks for Addresses

1. Implement Addresses structure containing the following uint8_t fields (the default value of each field shall be 0):

   - `version` - Generic packet version
   - `srcId` - Source device ID
   - `dstId` - Destination device ID
   - `port` - Communication port

2. Implement the specialization of the std::hash operator for the Addresses structure. The hash value shall have a type of uint32_t. It should be calculated using bitwise operators - the first byte of the hash value shall be equal to the version value, the second equal to srcId value, the third equal to dstId value, and the fourth equal to port value.
3. Add equality operator to Addresses structure which compares objects using the implemented hash operator
4. **_TestAddresses shall works right now_**

## **Packet**

Implementation shall be placed in [Packet.hpp](../AdvanceStructures/include/AdvanceStructures/Packet.hpp)

### General requirements for Packet

- The objects are considered equal when both addresses and timestamps are equal.
- One object is considered less than another when its timestamps are lower than another packet's. In the case of equal timestamps, the shorter (in the meaning of the payload size) packet is considered less than the other.

### Tasks for Packet

1. Implement Packet structure containing the following fields:

   - `addresses` - Addresses structure
   - `timestamp` - Timestamp in milliseconds
   - `payload` - RAW payload as vector of uint8_t

2. Implement the operator that allows using the std::find and std::sort methods from `algorithm` library.
3. **_TestPacket shall works right now_**

## **PacketFilterRule**

Implementation shall be placed in [PacketFilterRule.hpp](../AdvanceStructures/include/AdvanceStructures/PacketFilterRule.hpp)

### Tasks for PacketFilterRule

1. Implement FiltrationRule enum class of type uin8_t defining the following enumerators with meaning:

   - `ALLOW` - Configured address shall be passed by the filter
   - `DENY` - Configured address shall be blocked by the filter, others will be passed
   - `IGNORE` - Configured address shall be ignored by the filter (default value)

2. Implement Packet structure containing the following fields

   - `addresses` - Addresses structure
   - `versionFilterRule` - Generic packet version filtration rule (FiltrationRule type)
   - `srcIdFilterRule` - Source device ID filtration rule (FiltrationRule type)
   - `dstIdFilterRule` - Destination device ID filtration rule (FiltrationRule type)
   - `portFilterRule` - Communication port filtration rule (FiltrationRule type)

**_TestPacketFilterRule shall works right now_**

## **PacketFilter**

Implementation shall be placed in [PacketFilter.hpp](../AdvanceStructures/include/AdvanceStructures/PacketFilter.hpp)

### General requirements for PacketFilter

- Filter can contain multiple filtration rule (PacketFilterRule)
- DENY has the highest priority both alongside one rule as well as in case of multiple rules
- If at least one filter rule deny the packet, it shall be dropped
- If at least one filter rule allow the packet, it shall be passed
- If all rules ignore the packet (rule is transparent), it shall be passed as well
- If the list of filter rules is empty, the PacketFilter shall pass the packet

### Tasks for PacketFilter

1. Implement the PacketFilter class with the following constructors:

   - default constructor without parameters
   - constructor with the argument as const reference to a vector of filter rules

2. Implement the following methods:

   - `void addRecord(const PacketFilterRule &record)` - extend the filter filtration rules
   - `void clear()` - remove all filtration rules from filter
   - `bool shouldPass(const Packet &packet) const` - return true if packet shall be passed by the filter, false otherwise.

3. **_TestPacketFilter shall works right now_**

## **Trace**

Implementation shall be placed in [Trace.h](../AdvanceStructures/include/AdvanceStructures/Trace.h) and [Trace.cpp](../AdvanceStructures/src/Trace.cpp)

### Tasks for Trace

1. Implement the Trace class with the following constructor:

   - constructor with the argument as a unique trace name of type std::string

2. Implement the following methods and operators:

   ```c
   /// @brief Method used to save new packet in Trace
   /// @param rec packet to be saved in a file
   void append(const Packet &packet);

   /// @brief Handy insertion operator, internally it just call append method on provided trace instance
   /// @param trace instance of trace to save packets to
   /// @param packet packet to be saved in a trace
   /// @return reference to input trace, to be able to chain insertions
   friend Trace &operator<<(Trace &trace, const Packet &packet);

   /// @brief Getter for number of packets saved in trace
   /// @return number of packets saved in trace
   uint32_t getTotalPacketsCounter() const;

   /// @brief Getter for unique trace name
   /// @return unique trace name
   std::string getUniqueTraceName() const;

   /// @brief Getter for const reference to packets stored in trace
   /// @return const reference to packets stored in trace
   const std::vector<Packet> &getPackets() const;
   ```

3. **_TestTrace shall works right now_**

## **RouterConfig & Router**

Implementation shall be placed in [RouterConfig.hpp](../AdvanceStructures/include/AdvanceStructures/RouterConfig.hpp), [Router.h](../AdvanceStructures/include/AdvanceStructures/Router.h), and [Router.cpp](../AdvanceStructures/src/Router.cpp)

### General requirements for Router

1. The router class is configured using RouterConfig structure
2. The router class dynamically creates Trace classes according to configuration
3. For each configured route the instance of the filter and trace shall be created by the router
4. The router routes the packet to proper traces based on configured filtration rules
5. One packet can be routed to multiple traces
6. The router stores traces with all routed packets

### Tasks for Router

1. Implement the PacketRouteConfig structure containing the following fields

   - `uniqueTraceName` - Unique name of trace of type std::string
   - `filtrationRules` - vector of filtration rules

2. Implement the RouterConfig structure containing the following fields

   - `routes` - vector of PacketRouteConfig.

3. Implement the Router class with the following constructor:

   - constructor with the argument as const reference to RouterConfig

4. Implement the following methods and operators:

   ```c
   /// @brief Method that routes packets to traces according to filters configuration
   /// @param packet packet which shall be routed
   void routePacket(const Packet &packet);

   /// @brief Getter for const reference to traces map
   /// @return const reference to traces map
   const std::map<std::string, Trace> &getTraces();

   ```

5. **_TestRouter shall works right now_**
