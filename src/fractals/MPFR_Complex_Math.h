#pragma once
#include <mpfr.h>

//---------- return status ------------
typedef enum
{
    SUCCESS = 0,  // operation completed successfully
    NULL_POINTER, // null pointer passed
    ERR_INIT,     // variable not initialized
    ERR_NO_MEM,   // memory allocation failure
    ERR_MATH,     // invalid math domain
    ERR_UNKNOWN   // catch-all
} status;

// ----------- Properties ---------------

typedef struct
{
    mpfr_prec_t precision;
    mpfr_rnd_t round_mode;
} var_prop;

// ------------ temp vars --------------

typedef struct
{
    mpfr_t temp1, temp2, temp3, temp4;
} temp_var;

// -------- complex var -----------

typedef struct
{
    mpfr_t r, im;
} var_c;

// --------- WS initialising -----

status set_var_prop(var_prop *prop, const mpfr_prec_t prec, const mpfr_rnd_t rnd);
status set_temp_var(temp_var *temps, const var_prop *prop);
status clear_temp_var(temp_var *temps);

// ----------- complex number initiliasing -------------

status init_var_c(var_c *z, const var_prop *prop);
status clear_var_c(var_c *z);
status set_var_c(var_c *z_dst, const var_c *z_src, const var_prop *prop);
status set_var_c_double(var_c *z_dst, const double real, const double img, const var_prop *prop);
status set_var_c_zero(var_c *z);

//----------- math ---------------------------
status add_c(var_c *z_dst, const var_c *z1, const var_c *z2, const var_prop *var_prop);
status sub_c(var_c *z_dst, const var_c *z1, const var_c *z2, const var_prop *var_prop);
status mult_c(var_c *z_dst, const var_c *z1, const var_c *z2, const var_prop *var_prop, temp_var *temps);
status sqr_c(var_c *z_dst, const var_c *z_src, const var_prop *var_prop, temp_var *temps);
status conj_c(var_c *z_dst, const var_c *z_src, const var_prop *var_prop);
status abs_c(mpfr_t dst, const var_c *z_src, const var_prop *var_prop, temp_var *temps);

// ---------- debugs ------------------------
status print_c(const var_c *z, const var_prop *prop);
status print_c_prec(const var_c *z, const var_prop *prop, const int digits);
status mpfrx_c_to_str(char *buf, size_t n, const var_c *z, const var_prop *prop, const int digits);
