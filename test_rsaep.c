#include <stdio.h>
#include <gmp.h>
#include "rsaep.h"

int main()
{
    struct rsa_public_key rpk;
  
    mpz_t c;
    mpz_t rsa_mod;
    mpz_t pub_exp;
    mpz_t m_too_big;
    mpz_t m_too_small;
    mpz_t m_in_range;
    
    mpz_init(c);
    mpz_init(rsa_mod);
    mpz_init(pub_exp);
    mpz_init(m_too_big);
    mpz_init(m_too_small);
    mpz_init(m_in_range);

    mpz_set_ui(rsa_mod, 1501);
    mpz_set_ui(pub_exp, 5);

    mpz_init(rpk.rsa_modulus);
    mpz_init(rpk.public_exponent);
    mpz_set(rpk.rsa_modulus, rsa_mod);
    mpz_set(rpk.public_exponent, pub_exp);
    
    mpz_set_ui(m_too_big, 1501);
    mpz_set_si(m_too_small, -1);
    mpz_set_ui(m_in_range, 200);
    
    rsaep(&c, rpk, m_too_big);
    rsaep(&c, rpk, m_too_small);
    rsaep(&c, rpk, m_in_range);
}
