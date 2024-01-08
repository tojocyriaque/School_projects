#include "integral.h"
#include <stdio.h>

int main(){
    int n = 1000;

    float a = 3;
    float b = 10;

    float sur = integral_rectangle(a, b, n);
    float sur_tr = integral_trapeze(a, b, n);

    printf("Surface rectangle: %f\n", sur);
    printf("Surface trapeze: %f\n", sur_tr);

    return 0;
}
