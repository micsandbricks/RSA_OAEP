#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <gmp.h>

#include "rsa_structs.h"
#include "rsaep.h"

#define TEST_ANSWER 63

static void test_return_value_correct(void **state)
{
    int c_int;

    /* Where we will be storing our ciphertext. */
    mpz_t c;

    /* The message we are converting to ciphertext. */
    mpz_t m;

    /* The modulus and public exponent of the public key. */
    mpz_t rsa_mod;
    mpz_t pub_exp;
    
    rsa_public_key rsa_pub_key;
    
    /* Initialize all gmp variables. */
    mpz_init(c);
    mpz_init(m);
    mpz_init(rsa_pub_key.rsa_modulus);
    mpz_init(rsa_pub_key.public_exponent);
    mpz_init(rsa_mod);
    mpz_init(pub_exp);

    mpz_set_ui(m, 50);
    mpz_set_ui(rsa_mod, 101);
    mpz_set_ui(pub_exp, 3);

    mpz_set(rsa_pub_key.rsa_modulus, rsa_mod);
    mpz_set(rsa_pub_key.public_exponent, pub_exp);
        
    rsaep(&c, rsa_pub_key, m);

    assert_int_equal(mpz_get_ui(c), 63);
}

int main(void)
{
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(test_return_value_correct),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
