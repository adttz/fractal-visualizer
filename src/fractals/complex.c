#include "complex.h"

complex_num complex_init_num(complex_num z, int r, int im)
{
    z.r = r;
    z.im = im;
}

complex_num complex_addition(complex_num z1, complex_num z2)
{
    complex_num z;
    double new_r = z1.r + z2.r;
    double new_im = z1.im + z2.im;
    
    complex_init_num(z,new_r,new_im);
    return z;
}

complex_num complex_squared(complex_num z1)
{
    complex_num z;
    double new_r = z1.r*z1.r - z1.im*z1.im;
    double new_im = (2*z1.r*z1.im) ;
    
    complex_init_num(z,new_r,new_im);
    return z;
}





