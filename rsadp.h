#ifndef RSADP_H
#define RSADP_H

#include "key_structs.h"

void rsadp(mpz_t *m, struct rsa_private_key rsa_priv_key, mpz_t c);

/*  Function:
    rsadp 

    Purpose:
    This is the RSA decryption primitive. The modulus (n) and 
    public exponent (e) taken from an RSA public key pair (n,e)
    is used to generate an integer c: c = m^e mod n.
    
    Input:
    mpz_t *m: The message decrypted from the ciphertext c.
    struct rsa_private_key K: An RSA public key, where we get n and e.
    mpz_t c: Ciphertext representative from which we decrypt a message.

    Output:
    Void.
*/
void rsadp(mpz_t *m, struct rsa_private_key K, mpz_t c)
{
     
    mpz_t rsa_mod_sub_1;
    int c_out_of_range;

    mpz_init(rsa_mod_sub_1);
    mpz_sub_ui(rsa_mod_sub_1, K.rsa_modulus, 1);
    c_out_of_range = (mpz_cmp_ui(c, 0) < 0) ||\
                     (mpz_cmp(c, rsa_mod_sub_1) > 0);

    if (c_out_of_range)
    {
        printf("Ciphertext representative out of range.\n");
        return;
    }

    mpz_powm_sec(*m, c, K.private_exponent, K.rsa_modulus);
}

#endif
