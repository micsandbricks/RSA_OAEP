#include <stdio.h>
#include <gmp.h>
#include "rsadp.h"

int main()
{
    struct rsa_private_key K;
  
    mpz_t c;
    mpz_t rsa_mod;
    mpz_t priv_exp;
    mpz_t c_too_big;
    mpz_t c_too_small;
    mpz_t c_in_range;
    
    mpz_init(c);
    mpz_init(rsa_mod);
    mpz_init(priv_exp);
    mpz_init(c_too_big);
    mpz_init(c_too_small);
    mpz_init(c_in_range);

    mpz_set_ui(rsa_mod, 1501);
    mpz_set_ui(priv_exp, 5);

    mpz_init(K.rsa_modulus);
    mpz_init(K.private_exponent);
    mpz_set(K.rsa_modulus, rsa_mod);
    mpz_set(K.private_exponent, priv_exp);
    
    mpz_set_ui(c_too_big, 1501);
    mpz_set_si(c_too_small, -1);
    mpz_set_ui(c_in_range, 200);
    
    rsadp(&c, K, c_too_big);
    rsadp(&c, K, c_too_small);
    rsadp(&c, K, c_in_range);

    gmp_printf("c: %Zi\n", c);
}
