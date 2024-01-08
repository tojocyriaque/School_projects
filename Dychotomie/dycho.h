#include <stdio.h>
#include <alct.h>
#include "fonction.h"

/*
 *
 *  Fonction f(x) = ln(x) - 1
 *
*/

#define EPS 0.000001

float solution(float ta, float tb){
    float s = .0;
    float t = .0;
    
    float a = ta;
    float b = tb;

    while(fabs(b-a)>EPS){
        t = a+(b-a)/2;
        printf("%f\n", t);
        if( f(t)*f(b)<0 ){
            a = t;
        }
        else if( f(a)*f(t)<0 ){
            b = t;
        }
        printf("a=%f; b=%f\n", a, b);
    }
    s = a+(b-a)/2;
    return s;
}


