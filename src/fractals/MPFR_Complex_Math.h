#pragma once
#include <mpfr.h>
// ----Properties---------------

typedef struct
{
    mpfr_prec_t precision;
    mpfr_rnd_t round_mode;
}var_prop;

// ------------temp vars--------------

typedef struct
{
    mpfr_t temp1, temp2, temp3, temp4; 
}temp_var;

// --------complex var-----------

typedef struct
{
    mpfr_t r, im;
}var_c;

// ---------WS initialising-----

void set_var_prop(var_prop* prop, mpfr_prec_t prec, mpfr_rnd_t rnd); 
void set_temp_var(temp_var* temps, var_prop* prop);
void clear_temp_var(temp_var* temps);

// ----------- complex number initiliasing-------------

void init_var_c(var_c* z, const var_prop* prop);
void clear_var_c(var_c* z);
void set_var_c(var_c* z_dst, var_c* z_src, var_prop* prop);
void set_var_c_double(var_c* z_dst, double real, double img, var_prop* prop);
void set_var_c_zero(var_c* z);

//-----------

