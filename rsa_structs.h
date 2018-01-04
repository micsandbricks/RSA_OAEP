#ifndef KEY_STRUCTS_H
#define KEY_STRUCTS_H

#include <gmp.h>

/*  Structure:
    rsa_public_key
*/
struct rsa_public_key
{
    mpz_t rsa_modulus;
    mpz_t public_exponent;
};

/*  Structure:
    rsa_private_key
*/
struct rsa_private_key
{
    mpz_t rsa_modulus;
    mpz_t private_exponent;
};

/*  Structure:
    octet_string
 */
struct octet_string 
{
    char *str_pointer;
    int num_octets;
    int str_len;
    int error_detected;
};

/*  Structure:
    base_256_representation
*/
struct base_256_representation
{
    int *coeff_pointer;
    int num_coeffs;
};

#endif
