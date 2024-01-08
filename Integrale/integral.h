#include "fonction.h"

float surf(float a, float b){
    return fabs(b-a)*fabs(f(a));
}

float surf_triangle(float a, float b){
    return  ( fabs(b-a) * fabs(f(b)-f(a)) )/2;
}

float integral_trapeze(float a, float b, int n){
    float int_ = 0.;
    float step = (b-a)/n;

    for (float i=a+step; i<b; i+=step) {
        int_ += surf(i, i-step);
        int_ += surf_triangle(i, i-step);
    }
    return int_;
}

float integral_rectangle(float a, float b, int n){
    float int_ = 0;
    float step = (b-a)/n;

    for(float i=a+step; i<b; i+=step ){
        int_ += surf(i, i-step);
    }

    return int_;
}


