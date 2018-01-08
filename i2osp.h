#ifndef I2OSP_H
#define I2OSP_H

#include <gmp.h> /* For all handling of large numbers. */
#include <stdlib.h> /* For malloc. */
#include "rsa_structs.h"

octet_string i2osp(mpz_t x, int l);
base_256_representation to_base_256(mpz_t n, int l);


/*  i20sp
 
 
    Purpose:
    This function converts an integer to an octet string
    according to the specification in ROES.
   
    Input:
    mpz_t x: A non-negative integer to be converted.
    int l: Intended length of the octet string.
   
    Output:
    octet_string: A representation of the octet string
    obtained from the integer x.
*/
octet_string i2osp(mpz_t x, int l)
{

    int i;

    /* A boolean that is set to 1 if x => 256^l,
       is set to 0 otherwise. */
    int x_too_big;

    /* An integer used to set "x_too_big". Is simply
       set to 256^l. */
    mpz_t x_upper_bound;

    base_256_representation bs_256;

    /* The representation of the generated octet string.*/
    octet_string os;

    mpz_init(x_upper_bound);
    mpz_ui_pow_ui(x_upper_bound, 256, l);
    x_too_big = (mpz_cmp(x_upper_bound, x) < 0);

    /* If x is too big, deallocate octet_string and print
       an error message. */
    if (x_too_big)
    {
        printf("Integer too large.");
        free(os.str_pointer);
        os.num_octets = 0;
        os.error_detected = 1;
        return os;      
    }

    /* Fetch all the coefficients used to write x in representaiton base 256.*/
    bs_256 = to_base_256(x, l);

    /* Allocate pointer (4 chars per octet and 1 char for terminating character)*/
    os.str_pointer = (char *) malloc(l+1); 
    os.num_octets = l;
    os.error_detected = 0;

    for (i = 0; i < os.num_octets; i++)
        *(os.str_pointer + i) = *(bs_256.str_pointer + i);

    return os;
}

/*  to_base_256

    Purpose:
    Calculates coefficients for a l-digit representation base 256.
   
    Input:
    mpz_t n: The number which 256-coefficients we are looking for.
    int l: The number of coefficients we are going to return.

    Output:
    base_256_representation n_256_rep: A representation of the
    integer n in representation base 256.
*/
base_256_representation to_base_256(mpz_t n, int l)
{

    int i = 1;
    int l_diff;

    mpz_t q;
    mpz_t r;
    mpz_t base;
    mpz_t d;

    base_256_representation n_256_rep;

    n_256_rep.coeff_pointer = (int *) malloc(l);
    n_256_rep.num_coeffs = l;
    int current_coeff_index = 0;

    if (l < 1)
    {
        printf("Invalid l, choose a number => 1.");
        free(n_256_rep.coeff_pointer);
        n_256_rep.coeff_pointer = NULL;
        n_256_rep.num_coeffs = 0;
        return n_256_rep;
    }

    mpz_init(q);
    mpz_init(r);
    mpz_init(base);
    mpz_init(d);

    l_diff = l - i;
    mpz_set(r, n);
    mpz_set_ui(base, 256);
    while (l_diff > 0)
    {
        mpz_pow_ui(d, base, l_diff);
        mpz_fdiv_q(q, r, d);
        mpz_fdiv_r(r, r, d);
        *(n_256_rep.coeff_pointer + current_coeff_index) = mpz_get_ui(q);
        current_coeff_index++;
        i++;
        l_diff = l - i;
    }
    *(n_256_rep.coeff_pointer + current_coeff_index) = mpz_get_ui(r);


    return n_256_rep;
}

#endif
