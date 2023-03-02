#include <math.h>

// TODO: not for decimal
double 
pow(double x, double y) 
{
    if (y == 0) {
        return 1;
    } else {
        return x * pow(x, y-1);
    }
}
