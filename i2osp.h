#ifndef I2OSP_H
#define I2OSP_H

#include <gmp.h> /* For all handling of large numbers. */
#include <stdlib.h> /* For malloc. */
#include "rsa_structs.h"

struct octet_string i2osp(mpz_t x, int l);
struct base_256_representation to_base_256(mpz_t n, int l);
char hex_character(int hex_num);
void base_256_to_hex(struct octet_string os, struct base_256_representation bs_256);

/*  i20sp


    Purpose:
    This function converts an integer to an octet string
    according to the specification in ROES.
   
    Input:
    mpz_t x: A non-negative integer to be converted.
    int l: Intended length of the octet string.
   
    Output:
    octet_string: A representation of the octet string
    obtained from the integer x.
*/
struct octet_string i2osp(mpz_t x, int l)
{
    /* A boolean that is set to 1 if x => 256^l,
       is set to 0 otherwise. */
    int x_too_big;

    /* An integer used to set "x_too_big". Is simply
       set to 256^l. */
    mpz_t x_upper_bound;

    struct base_256_representation bs_256;

    /* The representation of the generated octet string.*/
    struct octet_string os;

    mpz_init(x_upper_bound);
    mpz_ui_pow_ui(x_upper_bound, 256, l);
    x_too_big = (mpz_cmp(x_upper_bound, x) < 0);

    /* If x is too big, deallocate octet_string and print
       an error message. */
    if (x_too_big)
    {
        printf("Integer too large.");
        free(os.str_pointer);
        os.str_pointer = NULL;
        os.num_octets = 0;
        os.str_len = 0;
        os.error_detected = 1;
        return os;      
    }

    /* Fetch all the coefficients used to write x in representaiton base 256.*/
    bs_256 = to_base_256(x, l);

    /* Allocate pointer (4 chars per octet and 1 char for terminating character)*/
    os.str_pointer = (char *) malloc((4*l)+1); 
    os.str_len = 4*l;
    os.num_octets = l;
    os.error_detected = 0;

    base_256_to_hex(os, bs_256);

    return os;
}

/*  to_base_256

    Purpose:
    Calculates coefficients for a l-digit representation base 256.
   
    Input:
    mpz_t n: The number which 256-coefficients we are looking for.
    int l: The number of coefficients we are going to return.

    Output:
    base_256_representation n_256_rep: A representation of the
    integer n in representation base 256.
*/
struct base_256_representation to_base_256(mpz_t n, int l)
{

    int i = 1;
    int l_diff;

    mpz_t q;
    mpz_t r;
    mpz_t base;
    mpz_t d;

    struct base_256_representation n_256_rep;

    n_256_rep.coeff_pointer = (int *) malloc(l);
    n_256_rep.num_coeffs = l;
    int current_coeff_index = 0;

    if (l < 1)
    {
        printf("Invalid l, choose a number => 1.");
        free(n_256_rep.coeff_pointer);
        n_256_rep.coeff_pointer = NULL;
        n_256_rep.num_coeffs = 0;
        return n_256_rep;
    }

    mpz_init(q);
    mpz_init(r);
    mpz_init(base);
    mpz_init(d);

    l_diff = l - i;
    mpz_set(r, n);
    mpz_set_ui(base, 256);
    while (l_diff > 0)
    {
        mpz_pow_ui(d, base, l_diff);
        mpz_fdiv_q(q, r, d);
        mpz_fdiv_r(r, r, d);
        *(n_256_rep.coeff_pointer + current_coeff_index) = mpz_get_ui(q);
        current_coeff_index++;
        i++;
        l_diff = l - i;
    }
    *(n_256_rep.coeff_pointer + current_coeff_index) = mpz_get_ui(r);


    return n_256_rep;
}

/*  base_256_to_hex

    Purpose:
    Takes a representation of a number in representation base 256 and generates
    a string that takes all the coefficients from the representation base and
    concatenates all corresponding hex representations "\xdd" (d being integers).

    Input:
    struct octet_string os: The octet_string struct that we are filling in.
    struct base_256_representation bs_256: The base 256 we are taking our hex codes
    from.

    Output:
    Void
*/
void base_256_to_hex(struct octet_string os, struct base_256_representation bs_256)
{

    int i;
    int os_index = 0;;
    int coeff_decimal;
    char first_hex_code_char;
    char second_hex_code_char;

    for (i = 0; i < bs_256.num_coeffs; i++)
    {
        coeff_decimal = *(bs_256.coeff_pointer + i);
        first_hex_code_char = hex_character(coeff_decimal / 16);
        second_hex_code_char = hex_character(coeff_decimal % 16);

        *(os.str_pointer + os_index) = '\\';
        os_index++;
        *(os.str_pointer + os_index) = 'x';
        os_index++;
        *(os.str_pointer + os_index) = first_hex_code_char;
        os_index++;
        *(os.str_pointer + os_index) = second_hex_code_char;
        os_index++;
    }
    *(os.str_pointer + os_index) = '\0';
}

/*  hex_character

    Purpose:
    A function used to get a hexadecimal character for an integer.

    Input:
    int hex_num: The number we want a hex character for.

    Output:
    char: The hexadecimal character corresponding to hex_num.
*/
char hex_character(int hex_num)
{
    switch (hex_num){
        case 10:
            return 'a';
        case 11:
            return 'b';
        case 12:
            return 'c';
        case 13:
            return 'd';
        case 14:
            return 'e';
        case 15:
            return 'f';
        default:
            return hex_num + '0';
    }
}
#endif
