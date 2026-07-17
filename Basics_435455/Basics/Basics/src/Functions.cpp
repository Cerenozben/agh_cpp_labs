#include <Basics/Functions.h>

#include <algorithm>
#include <cmath>
#include <numbers>
#include <string>

namespace basics
{
// student code begin
//1. question
double mean(std::array<double,3>numbers){
    return (numbers[0] + numbers[1] + numbers[2])/3.0;
}
//2. question
double celsiusToFahrenheit(double celsius){
    return celsius*(9.0/5.0)+32;
}
//3. question
double findMax(std::array<double,3>numbers){
    return std:: max({numbers[0], numbers[1], numbers[2]});
}
//4. question
double calculateCircleArea(double radius){
    return std::numbers::pi*radius*radius;
}
//5. question
bool isPalindrome(uint32_t number){
    std::string s = std::to_string(number);
    std::string rs=s;
    std::reverse(rs.begin(), rs.end());
    return s == rs;
}
// student code end

}  // namespace basics