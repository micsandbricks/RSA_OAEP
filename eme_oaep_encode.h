#ifndef EME_OAEP_ENCODE_H
#define EME_OAEP_ENCODE_H

#include <stdlib.h>
#include "hash.h"
#include "rsa_structs.h"

#include <openssl/sha.h>

octet_string eme_oaep_encode(octet_string M, octet_string P, int emLen);

/*  Function:
    eme_oaep_encode

    Purpose:
    This function maps a message M to and encoded message EM using some 
    "encoding parameters" P and a hash function (here SHA256 is used).

    Input:
    octet_string M: The message octet string we want to encode,
    can at most be of length em_len - 1 - 2*h_len.
    octet_string P: The encoding parameters used to encode M.
    int em_len: The intended length in octets of the encoded message.

    Output:
    octet_string EM: The encoded message, an octet string of length 
    em_len.

    NOTE:
    The specification talks about potential problems with P being too
    long (the upper limit being the input limit of the sha256 function) and 
    thusly has error checking for this case. For the time being, this error 
    checking is disregarded, since it is improbable the length of P comes
    close to the input limit, is in the order of exabytes.
    
*/
octet_string eme_oaep_encode(octet_string M, octet_string P, int em_len)
{

    int i;
    octet_string PS;
    octet_string DB;

    int h_len = SHA256_DIGEST_LENGTH;
    int message_upper_limit = em_len - 2*h_len - 1;
    int ps_num_octets = em_len - M.str_len - 2*h_len - 1;
    
    unsigned char *p_hash;

    int P_hashing_successful;

    if (M.str_len <= message_upper_limit)
    {
        printf("Message too long.");
    }

    PS.str_pointer = (char *) malloc(ps_num_octets + 1);
    PS.num_octets = ps_num_octets;
    PS.error_detected = 0;
    
    p_hash =  (unsigned char *) malloc(h_len + 1);
    P_hashing_successful = generate_sha_256_hash(P.str_pointer, 
                                                P.str_len,
                                                p_hash);
}

#endif
