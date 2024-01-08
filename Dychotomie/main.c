#include "dycho.h"

/*
 *
 *  f(x) = 2ln(x)-1
 *
 * */

int main(){
    float a = -200;
    float b = 300;
    float s = solution(a, b);
    
    printf("\nSolution: %f\n", s);
    return 0;
}
