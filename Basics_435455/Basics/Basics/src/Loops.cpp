#include <Basics/Loops.h>
#include <sys/types.h>

#include <cstdint>

namespace basics
{
int forExercise1()
{
    // student code begin
    int sum = 0;
    for(int i=0; i<50; i++){
        sum += i;
    }
    return sum;
    // student code end
}

std::array<std::pair<std::string, std::string>, 2> forExercise2(std::array<std::string, 2> names,
                                                                std::array<std::string, 2> surnames)
{
    // student code begin
    std::array<std::pair<std::string,std::string>,2>result;
    for(size_t i=0; i<2; i++){
       result[i] = std::make_pair(names[i], surnames[i]);
}
    return result;
    // student code end
}

uint32_t forExercise3(uint32_t n)
{
    // student code begin
    uint32_t result=1;
    for(uint32_t i=0; i<=n; i++){
        result+=i;
    }
    return result;
    // student code end
}

uint8_t forExercise4(uint8_t value)
{
    // student code begin
    uint8_t count = 0;
    for(int i = 7; i>=0; --i){
        if((value>>i)&1){
            break;
        }
        count++;
    }
    return count;
    // student code end
}

int whileExercise1(std::array<int, 10> numbers)
{
    // student code begin
    int iterations = 0;
    int sum = 0;
    while (iterations < 10 && sum <= 100){
        sum+= numbers[static_cast<size_t>(iterations)];
        iterations++;
    }
    return iterations;
    // student code end
}

uint32_t whileExercise2(uint32_t base, uint32_t limit)
{
    // student code begin
    uint32_t exponent = 0;
    uint64_t current_value = 1;
    while(current_value <= limit){
        current_value *= base;
        exponent++;
    }
    return exponent;
    // student code end
}

}  // namespace basics