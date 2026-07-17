#include <Basics/FlowControl.h>

#include <iostream>

namespace basics
{
void ifExercise1(int arg)
{
    // student code begin
    if(arg>100){
        std::cout<<arg<<std::endl;
    }
    // student code end
}

bool ifElseExercise1(int arg)
{
    // student code begin
    if(arg>100){
        return true;
    }else{
        return false;
    }
    // student code end
}

int ifElseIfElseExercise1(int arg)
{
    // student code begin
    if (arg<0){
        return -1;
    }else if(arg==0){
        return 0;
    }else{
        return 1;
    }
    // student code end
}

float switchCaseExercise1(float a, char arithmeticOperator, float b)
{
    // student code begin
    switch(arithmeticOperator){
        case '+':
          return a+b;
        case '-':
          return a-b;
        case '*':
          return a*b;
        case '/':
          return a/b;
        default:
         return 0.0f;    
    }

    // student code end
}

int ternaryOperatorExercise1(unsigned int arg)
{
    // student code begin
    return(arg%2 == 0)? 1 : -1;
    // student code end
}

}  // namespace basics