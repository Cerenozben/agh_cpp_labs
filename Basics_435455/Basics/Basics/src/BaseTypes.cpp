#include <Basics/BaseTypes.h>

#include <cmath>
#include <cstdint>
#include <iostream>

namespace basics
{
bool boolExercise1(bool a, bool b)
{
    // student code begin
    if(a==true && b==true){
    return true;
    }else{
        return false;
    }
    // student code end
}

bool boolExercise2(bool a, bool b)
{
    // student code begin
     if(a!=b){
        return true;
     }else{
        return false;
     }
    // student code end
}

bool boolExercise3(bool a, bool b)
{
    // student code begin
    if(a==true || b==true){
        return true;
    }else{
        return false;
    }
    // student code end
}

bool boolExercise4(bool a)
{
    // student code begin
    if(a==false){
        return true;
    }else{
        return false;
    }
    // student code end
}

int16_t shortExercise1(int16_t arg)
{
    // student code begin
    return arg++;
    // student code end
}

void intExercise1(int arg)
{
    // student code begin
    std::cout<<arg<<std::endl;
    // student code end
}

bool intExercise2(int arg)
{
    // student code begin
    if(arg>=10){
        return true;
    }else{
        return false;
    }
    // student code end
}

unsigned int uintExercise1(unsigned int a, unsigned int b)
{
    // student code begin
    unsigned int sum= a+b;
    return sum;
    // student code end
}

unsigned int uintExercise2(unsigned int a, unsigned int b)
{
    // student code begin
    if(a<b){
        return a;
    }else{
        return b;
    }
    // student code end
}

float floatExercise1(float a, float b)
{
    // student code begin
    float multiplication= a*b;
    return multiplication;
    // student code end
}

double doubleExercise1(double a, double b)
{
    // student code begin
    double absA = std:: abs(a);
    double absB = std:: abs(b);
    if(absA>absB){
        return absA;
    }else{
        return absB;
    }
    // student code end
}

bool doubleExercise2(double a, double b, double c)
{
    // student code begin
    double sum= a+b;
    double epsilon = 0.000001;
    if(std::abs(sum-c)<epsilon){
        return true;
    }else{
        return false;
    }
    // student code end
}

}  // namespace basicss