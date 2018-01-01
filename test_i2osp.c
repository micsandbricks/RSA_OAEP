#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "i2osp.h"
#include "os2ip.h"

int main()
{
    struct octet_string os;
    mpz_t n;
    mpz_t m;
    int l;

    mpz_init(n);
    mpz_init(m);

    mpz_set_ui(n, 2250401);
    l = 10;

    os = i2osp(n, l);
    printf("os string: %s\n", os.str_pointer);

    os2ip(&m, os);
    gmp_printf("m: %Zi\n", m);
}
