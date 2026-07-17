#include <Basics/ArrayPairString.h>

#include <array>
#include <string>
#include <utility>

namespace basics
{
std::pair<double, bool> pairExercise1(double first, bool second)
{
    // student code begin
    return{first,second};
    // student code end
}

std::pair<bool, bool> pairExercise2(int number)
{
    // student code begin
    return {number>0, number%2 == 0};
    // student code end
}

std::pair<double, int> pairExercise3(std::pair<int, double> toSwap)
{
    // student code begin
    return{toSwap.second, toSwap.first};
    // student code end
}

std::array<int, 3> arrayExercise1()
{
    // student code begin
    return {1,2,3};
    // student code end
}

int arrayExercise2(const std::array<int, 3> arg)
{
    // student code begin
    return arg[1];
    // student code end
}
int arrayExercise3(const std::array<int, 3> arg)
{
    // student code begin
    return arg.front() + arg.back();
    // student code end
}

bool arrayExercise4(const std::array<int, 3> &a, const std::array<int, 5> &b)
{
    // student code begin
    for(size_t i=0; i<=2; i++){
        if(b[i]==a[0] && b[i+1]==a[1] && b[i+2]== a[2]){
            return true;
        }
    }
    return false;
    // student code end
}

int stringExercise1(const std::string &arg)
{
    // student code begin
    return static_cast<int>(arg.size());
    // student code end
}

std::string stringExercise2(const std::string &a, const std::string &b)
{
    // student code begin
    return a+b;
    // student code end
}

std::string stringExercise3(std::string arg)
{
    // student code begin
    arg.replace(0,1,"Hello");
    return arg;
    // student code end
}

bool stringExercise4(const std::string &str, const std::string &substring)
{
    // student code begin
    return str.find(substring) < str.length();
    // student code end
}

std::string stringExercise5(std::string arg)
{
    // student code begin
    for(size_t i = 0; i < arg.length(); i++){
        arg[i] = static_cast<char>(std::toupper(arg[i]));
    }
    return arg;
    // student code end
}

int stringExercise6(const std::string &str, char c)
{
    // student code begin
    int count = 0;
    for(size_t i = 0; i<str.length(); i++){
        if(str[i] == c){
            count++;
        }
    }
    return count;
    // student code end
}

std::string stringExercise7(const std::string &str, size_t pos, size_t len)
{
    // student code begin
    return str.substr(pos,len);
    // student code end
}

bool stringExercise8(const std::string &str, const std::string &prefix)
{
    // student code begin
    if (str.length() < prefix.length()){
    return false;
    }
    return str.substr(0, prefix.length()) == prefix;
    // student code end
}

}  // namespace basics