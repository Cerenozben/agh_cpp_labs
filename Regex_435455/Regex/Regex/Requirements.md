# Regex

## Useful links

- [https://en.wikipedia.org/wiki/Regular_expression]
- [https://coderpad.io/blog/development/the-complete-guide-to-regular-expressions-regex/]
- [https://en.cppreference.com/w/cpp/regex]
- [https://en.cppreference.com/w/cpp/regex/regex_match]
- [https://en.cppreference.com/w/cpp/regex/regex_search]
- [https://en.cppreference.com/w/cpp/regex/regex_replace]
- [https://cplusplus.com/reference/regex/match_results/]
- [https://cplusplus.com/reference/regex/regex_iterator/regex_iterator/]
- [https://www.studyplan.dev/pro-cpp/regex-capture-groups]
- [https://en.cppreference.com/w/cpp/utility/optional]
- [https://regex101.com/]
- [https://www.youtube.com/watch?v=79WVN-vGllU]

## **BasicRegex**

### **Prototypes are defined in BasicRegex.h**

### **Implementation should be done in BasicRegex.cpp**

1. Implement function "validateEmail" function should take as argument const string reference and validating if string are proper email address using regex
2. Implement function "removeWhitespace" function should take as argument const string reference and returning string without whitespace using regex
3. Implement function "extractDomain" function is used to extract the domain from an email address. It takes a const string reference containing the email address as an argument and returns a string with the domain name. If there is no domain in the email address, an empty string is returned.

### TestBasicRegex at this point should work

## **ComplexRegex**

### **Prototypes are defined in ComplexRegex.h**

### **Implementation should be done in ComplexRegex.cpp**

1. Implement the function countMatches that calculates the number of specified words occurrences in a sentence. If the words vector is empty, the function shall return 0, otherwise, it shall return the sum of occurrences of every word from words vector.
2. Implement the function swapCatchGroups that takes string sentences and regex pattern. This function shall swap the content of two catch groups defined in the regex pattern and return the modified string. This function shall return a modified string only when there are exactly two matches defined by catch groups, otherwise, it shall return an unmodified sentence. Example behavior:

   ```c
   const std::string sentence = "Ubuntu is the worst system in the world. Windows is the best system in the world.";
   const std::string expectedResult = swapCatchGroups(sentence, std::regex(R"(^.*(Ubuntu).*(Windows).*$)"));
   /// The value of expectedResult is "Windows is the worst system in the world. Ubuntu is the best system in the world."
   ```

3. Implement the function fillTemplateString that takes a string template with named arguments inside braces {} and a map of arguments that shall replace the named arguments in the template. If the argument occurs multiple times, every occurrence shall be replaced. More arguments in the arguments map than defined in the template are acceptable. When the argument exists in the template, but is not defined in the arguments map, it shall be skipped. Example behavior:

   ```c
   const std::string templateString = "My name is {name}. I am {years} years old.";
   const std::map<std::string, std::string> args{{"name", "Mike"}, {"years", "32"}};
   const auto expectedResult = fillTemplateString(templateString, args);
   /// The value of expectedResult is "My name is Mike. I am 32 years old.";
   ```

4. Implement the function sortByCatchGroupValue which takes a reference to a vector of sentences and a regex pattern. This function shall sort sentences using the value from the catch group in ascending order. The sorting shall be performed only if every sentence matches the regex pattern, otherwise, the sentence vector shall be untouched. Example behavior:

   ```c
   std::vector<std::string> sentences{"LOGFILE_TIME_235959_DATE_20240511_INDEX_0003.txt",
                                      "LOGFILE_TIME_213700_DATE_20240518_INDEX_0004.txt",
                                      "LOGFILE_TIME_192402_DATE_20240512_INDEX_0002.txt",
                                      "LOGFILE_TIME_173406_DATE_20240421_INDEX_0001.txt"};

   const std::vector<std::string> sortedSentences{"LOGFILE_TIME_173406_DATE_20240421_INDEX_0001.txt",
                                                  "LOGFILE_TIME_192402_DATE_20240512_INDEX_0002.txt",
                                                  "LOGFILE_TIME_213700_DATE_20240518_INDEX_0004.txt",
                                                  "LOGFILE_TIME_235959_DATE_20240511_INDEX_0003.txt"};

   std::regex timeCatchGroup(R"(^LOGFILE_TIME_(\d{6})_DATE_\d{8}_INDEX_\d{4}.txt$)");

   sortByCatchGroupValue(sentences, timeCatchGroup);

   /* The value of sentences is: {"LOGFILE_TIME_173406_DATE_20240421_INDEX_0001.txt",
                                  "LOGFILE_TIME_192402_DATE_20240512_INDEX_0002.txt",
                                  "LOGFILE_TIME_213700_DATE_20240518_INDEX_0004.txt",
                                  "LOGFILE_TIME_235959_DATE_20240511_INDEX_0003.txt"}
   */
   ```

### TestComplexRegex at this point should work

## **NmeaParser**

In this exercise, the basic parser for NMEA GNGGA messages shall be implemented. In tests, messages with a limited number of GNGGA signals are used.

### NMEA0183 Standard

- [https://en.wikipedia.org/wiki/NMEA_0183] Only if you are curious.

### GNGGA message format used in exercise and example parsed values

The NMEA messages format is generally simple - a comma separates the messages fields and every single message ID defines its unique number and meaning of fields. The messages are transmitted in human-readable ASCII format.

**GNGGA message fields**:

1. Message ID
2. UTC time of position fix, in hhmmss.ss format. Hours must be two numbers, so may be padded. For example, 7 is shown as 07.
3. Latitude, in degrees and decimal minutes (ddmm.mmmmmmmm)
4. Direction of latitude (N: North, S: South).
5. Longitude, in degrees and decimal minutes (dddmm.mmmmmmmm). Should contain three digits of ddd.
6. Direction of longitude: (E: East, W: West)
7. GPS Quality indicator:
   - 0x00: Fix not valid
   - 0x01: GPS fix
   - 0x02: Differential GPS fix (DGNSS), SBAS, OmniSTAR VBS, Beacon, RTX in GVBS mode
   - 0x03: Not applicable
   - 0x04: RTK Fixed, xFill
   - 0x05: RTK Float, OmniSTAR XP/HP, Location RTK, RTX
   - 0x06: INS Dead reckoning

**Example GNGGA message:**

- GNGGA,223831.45,4238.94181577,N,08309.18413513,W,4

**Parsed NMEA GNGGA fields:**

- **Message ID**: GNGGA
- **UTC time**: 223831.45
- **Latitude degrees**: 42
- **Latitude minutes**: 38.94181577
- **Direction of latitude**: N
- **Latitude**: Degrees + Minutes / 60.0 = 42.6490302628
- **Longitude degrees**: 83
- **Longitude minutes**: 9.18413513
- **Direction of longitude**: W
- **Longitude**: Degrees + Minutes / 60.0 = -83.1530689188 (Western hemisphere = negative sign)
- **GPS Quality indicator**: 0x04 (RTK Fixed, xFill)

Important: Coordinate in the Southern and Western hemispheres shall have a negative sign.

### **Prototypes are defined in NmeaParser.h**

### **Implementation should be done in NmeaParser.cpp**

1. Implement the function sortByCatchGroupValue which takes the NMEA GNGGA message as a string and returns parsed GPS coordinates as nmeaParser::GpsCoordinates structure. This function returns the structure as an optional value, meaning that this value may be filled or not. The value shall only be filled if the sentence NMEA message string meets the requirements of the GNGGA message format. Otherwise, the returned value must be std::nullopt.

### TestNmeaParser at this point should work

## **NamedRegex**

In this exercise, you will need to implement a class providing a named capturing group feature. What is the key problem? The standard C++ regex library does not support such a feature.

### Named capturing group

A named capturing group is a particular kind of capturing group that allows to give a name to the group. The group's matching result can later be identified by this name instead of by its index in the pattern.

Syntax: `(?<name>pattern)`

where:

- `pattern` - A pattern consisting of anything you may use in a regex literal, including a disjunction.
- `name` - The name of the group. Must be a valid identifier.

Example:

- Regex pattern: `^(?<VendorName>.+)_(?<ProductType>.+)_(?<SerialNumber>\d{6})_(?<Date>\d{8})_(?<Time>\d{6})$`
- Input string: `Samsung_GalaxyS24_765132_20250403_163412`
- Result: the map containing values from the named capturing groups (`VendorName: Samsung`, `ProductType: GalaxyS24`, `SerialNumber: 765132`, etc.)

Description based on:

- [https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Regular_expressions/Named_capturing_group]

### Requirements

- Student shall provide the NamedRegex class implementation in NamedRegex.h & NamedRegex.cpp file,
- The public method declarations (with Doxygen documentation) are provided and should not be changed,
- The regex template (pattern) is considered valid if it contains at least one named capture group with the expected syntax,
- The values of the named capture group shall be returned as a map of variants (defined as NamedParameters),
- If the value captured by the named group can be interpreted as an integer, it should be returned as a uint64_t. Otherwise, the value should be of type std::string,
- NamedParameters should contain only values ​​from named groups. Regular catch groups should be ignored,
- The methods must be implemented according to their Doxygen documentation.

### TestNamedRegex at this point should work
