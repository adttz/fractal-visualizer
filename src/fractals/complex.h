#pragma once

struct complex_number
{
    double r;
    double im;
}typedef complex_num;

complex_num complex_init_num(complex_num z, int r, int im);
complex_num complex_addition(complex_num z1, complex_num z2);
complex_num complex_squared(complex_num z1);