#ifndef RSAEP_H
#define RSAEP_H

#include "rsa_structs.h"

/*  Function: 
    rsaep
 
    Purpose:
    This is the RSA encryption primitive. The modulus (n) and 
    public exponent (e) taken from an RSA public key pair (n,e)
    is used to generate an integer c: c = m^e mod n.

    Input:
    mpz_t *c: The integer that is generated.
    struct rsa_public_key rsa_pub_key: An RSA public key, where we get n and e.
    mpz_t m: A message integer used to generate c. 

    Output:
    Void.
*/
void rsaep(mpz_t *c, struct rsa_public_key rsa_pub_key, mpz_t m)
{
    mpz_t rsa_mod_sub_1;
    int m_out_of_range;

    mpz_init(rsa_mod_sub_1);
    mpz_sub_ui(rsa_mod_sub_1, rsa_pub_key.rsa_modulus, 1);
    m_out_of_range = (mpz_cmp_ui(m, 0) < 0) ||\
                     (mpz_cmp(m, rsa_mod_sub_1) > 0);

    if (m_out_of_range)
    {
        printf("Message representative out of range.\n");
        return;
    }

    mpz_powm_sec(*c, m, rsa_pub_key.public_exponent, rsa_pub_key.rsa_modulus);
}

#endif
