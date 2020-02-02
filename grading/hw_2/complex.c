#include "complex.h"
#include <stdlib.h>
#include <math.h>

Complex add ( Complex a, Complex b ){
    return (Complex) { a.real + b.real, a.im + b.im };
}

Complex multiply ( Complex a, Complex b ){
    return (Complex) { (a.real * b.real) - (a.im * b.im), (a.real * b.im) + (a.im * b.real) };
}

Complex negate ( Complex a ){
    return (Complex) { a.real * -1.0, a.im * -1.0 };
}

double magnitude ( Complex a ){
    return { sqrt(a.real*a.real + a.im*a.im) };
}