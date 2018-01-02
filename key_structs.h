#ifndef KEY_STRUCTS_H
#define KEY_STRUCTS_H

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

#endif
