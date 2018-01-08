#ifndef KEY_STRUCTS_H
#define KEY_STRUCTS_H

#include <gmp.h>

/*  Structure:
    rsa_public_key
*/
typedef struct rsa_public_key
{
    mpz_t rsa_modulus;
    mpz_t public_exponent;
} rsa_public_key;

/*  Structure:
    rsa_private_key
*/
typedef struct rsa_private_key
{
    mpz_t rsa_modulus;
    mpz_t private_exponent;
} rsa_private_key;

/*  Structure:
    octet_string
 */
typedef struct octet_string 
{
    char *str_pointer;
    int num_octets;
    int error_detected;
} octet_string;

/*  Structure:
    base_256_representation
*/
typedef struct base_256_representation
{
    int *coeff_pointer;
    int num_coeffs;
} base_256_representation;

#endif
