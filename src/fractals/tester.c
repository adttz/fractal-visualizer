#include <stdio.h>
#include <stdlib.h>
#include "MPFR_Complex_Math.h"

int main(void) {
    var_prop prop;
    temp_var temps;
    var_c z1, z2, z3;
    mpfr_t absval;

    // -------- Context Setup --------
    if (set_var_prop(&prop, 256, MPFR_RNDN) != SUCCESS) {
        printf("Failed to set properties\n");
        return EXIT_FAILURE;
    }

    if (set_temp_var(&temps, &prop) != SUCCESS) {
        printf("Failed to init temp vars\n");
        return EXIT_FAILURE;
    }

    if (init_var_c(&z1, &prop) != SUCCESS ||
        init_var_c(&z2, &prop) != SUCCESS ||
        init_var_c(&z3, &prop) != SUCCESS) {
        printf("Failed to init complex vars\n");
        return EXIT_FAILURE;
    }

    mpfr_init2(absval, prop.precision);

    // -------- Basic Set Tests --------
    printf("\n== Initialization Tests ==\n");
    set_var_c_str(&z1, "1.55555555555555555", "-2.2577777777777777", &prop);
    set_var_c_str(&z2, "-0.7555555555", "4.125111111111111111111111", &prop);
    print_c(&z1, &prop);
    print_c(&z2, &prop);

    // -------- Copy & Zero --------
    printf("\n== Copy & Zero ==\n");
    set_var_c(&z3, &z1, &prop);
    print_c(&z3, &prop);
    set_var_c_zero(&z3);
    print_c(&z3, &prop);

    // -------- Add/Sub --------
    printf("\n== Add/Sub ==\n");
    add_c(&z3, &z1, &z2, &prop);
    print_c_prec(&z3, &prop, 20);
    sub_c(&z3, &z1, &z2, &prop);
    print_c(&z3, &prop);

    // -------- Multiply --------
    printf("\n== Multiplication ==\n");
    mult_c(&z3, &z1, &z2, &prop, &temps);
    print_c(&z3, &prop);

    // -------- Square --------
    printf("\n== Square ==\n");
    sqr_c(&z3, &z1, &prop, &temps);
    print_c(&z3, &prop);

    // -------- Conjugate --------
    printf("\n== Conjugate ==\n");
    conj_c(&z3, &z2, &prop);
    print_c(&z3, &prop);

    // -------- Absolute Value --------
    printf("\n== Absolute Value ==\n");
    abs_c(absval, &z2, &prop, &temps);
    mpfr_printf("|z2| = %.70Rf\n", absval);


    printf("\n Testing print_c_prec...\n");
    var_c z;
    init_var_c(&z, &prop);
    set_var_c_double(&z, 3.14159265358979, -2.718281828459, &prop);

    // print_c(&z, &prop); // 10 decimal digits
    print_c_prec(&z, &prop, 20); // 20 decimal digits

    printf("Testing set_var_c_str...\n");
    var_c z_str;
    if (init_var_c(&z_str, &prop) == SUCCESS) {
        set_var_c_str(&z_str, "3.14159265358979", "-2.7182818284590452353602874713526624977572", &prop);
        print_c_prec(&z_str, &prop, 50); // should print pi and -e with 50 digits
        clear_var_c(&z_str);
}


    // -------- Stress Test --------
    printf("\n== Stress Test (randomized) ==\n");
    for (int i = 0; i < 5; i++) {
        double a = (rand() % 1000) / 100.0;
        double b = (rand() % 1000) / 100.0;
        double c = (rand() % 1000) / 100.0;
        double d = (rand() % 1000) / 100.0;

        set_var_c_double(&z1, a, b, &prop);
        set_var_c_double(&z2, c, d, &prop);
        mult_c(&z3, &z1, &z2, &prop, &temps);

        char buf[256];
        c_to_str(buf, sizeof(buf), &z3, &prop, 20);
        printf("[%d] (%f+%fi) * (%f+%fi) = %s\n",
               i, a, b, c, d, buf);
    }

    // -------- Cleanup --------
    clear_var_c(&z1);
    clear_var_c(&z2);
    clear_var_c(&z3);
    clear_temp_var(&temps);
    mpfr_clear(absval);

    printf("\nSanity check completed!\n");
    return EXIT_SUCCESS;
}
