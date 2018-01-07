#include <stdio.h>
#include "rsa_structs.h"
#include "eme_oaep_encode.h"

int main()
{
    struct octet_string M;
    struct octet_string P;
    struct octet_string EM;
    int emLen = 90;

    M.str_pointer = (char *) malloc(12 + 1);
    M.num_octets = 3;
    M.str_len = 12;
    M.error_detected = 0;

    M.str_pointer[0] = '\\';
    M.str_pointer[1] = 'x';
    M.str_pointer[2] = '0';
    M.str_pointer[3] = '0';
    M.str_pointer[4] = '\\';
    M.str_pointer[5] = 'x';
    M.str_pointer[6] = '0';
    M.str_pointer[7] = '1';
    M.str_pointer[8] = '\\';
    M.str_pointer[9] = 'x';
    M.str_pointer[10] = '1';
    M.str_pointer[11] = '0';
    M.str_pointer[12] = '\0';

    P.str_pointer = (char *) malloc(4 + 1);
    P.num_octets = 1;
    P.str_len = 4;
    P.error_detected = 0;

    P.str_pointer[0] = '\\';
    P.str_pointer[1] = 'x';
    P.str_pointer[2] = '0';
    P.str_pointer[3] = '0';
    P.str_pointer[4] = '\0';


    EM = eme_oaep_encode(M, P, emLen);
}
