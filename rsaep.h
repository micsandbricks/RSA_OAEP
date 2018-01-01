#ifndef RSAEP_H
#define RSAEP_H

struct rsa_public_key
{
    mpz_t rsa_modulus;
    mpz_t public_exponent;
};

void rsaep(mpz_t *c, struct rsa_public_key rpk, mpz_t m)
{
    mpz_t rsa_mod_sub_1;
    int m_out_of_range;

    mpz_init(rsa_mod_sub_1);
    mpz_sub_ui(rsa_mod_sub_1, rpk.rsa_modulus, 1);
    m_out_of_range = (mpz_cmp_ui(m, 0) < 0) ||\
                     (mpz_cmp(m, rsa_mod_sub_1) > 0);

    gmp_printf("m: %Zi\n", m);
    if (m_out_of_range)
        printf("Message representative out of range.\n");
}


#endif
