#ifndef OS2IP_H
#define OS2IP_H

#include <gmp.h>
#include "rsa_structs.h"

void os2ip(mpz_t *n, octet_string os);
void int_from_base_256(mpz_t *n, int octets[], int num_octets);

/*  os2ip

    Purpose:
    A function used to convert an octet string to an integer.

    Input:
    mpz_t *n: The integer to be generated by the octet string.
    octet_string os: The octet string used to generate integer.

    Output:
    Void.
*/
void os2ip(mpz_t *n, octet_string os)
{
    int_from_base_256(n, os.str_pointer, os.num_octets);
}


/*  int_from_base_256

    Purpose:
    Generate an integer using representation base 256, the coefficients
    of each base taken from the octets array.

    Input:
    mpz_t *n: The integer to be generated. 
    int octets[]: An array of octets used as coefficients in representation 
    base 256.
    int num_octets: The number of elements in octets.

    Output:
    Void.
*/
void int_from_base_256(mpz_t *n, int octets[], int num_octets)
{
    int octet_index = 0;
    int l_diff;
    mpz_t base;
    mpz_t m;
    mpz_t coeff;

    mpz_init(base);
    mpz_init(m);
    mpz_init(coeff);

    mpz_set_ui(base, 256);

    l_diff = num_octets - 1;
    while (l_diff > 0)
    {
        mpz_pow_ui(coeff, base, l_diff);
        mpz_mul_ui(coeff, coeff, octets[octet_index]);
        mpz_add(m, m, coeff);
        octet_index++;
        l_diff--;
    }
    mpz_add_ui(m, m, octets[octet_index]);

    mpz_set(*n, m);
}

#endif
