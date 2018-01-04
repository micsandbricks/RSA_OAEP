#ifndef EME_OAEP_ENCODE_H
#define EME_OAEP_ENCODE_H

#include <stdlib.h>
#include "rsa_structs.h"

/* OpenSSL headers */
#include "openssl/sha.h"

struct octet_string eme_oaep_encode(struct octet_string M, struct octet_string P, int emLen);

/*  Function:
    eme_oaep_encode

    Purpose:
    This function maps a message M to and encoded message EM using some "encoding parameters" P
    and a hash function (here SHA256 is used).

    Input:
    struct octet_string M: The message octet string we want to encode, can at most be of length
    emLen - 1 -2hlen.
    struct octet_string P: The encoding parameters used to encode M.
    int emLen: The intended length in octets of the encoded message, at least 2hLen + 1.

    Output:
    struct octet_string EM: The encoded message, an octet string of length emLen.
*/
struct octet_string eme_oaep_encode(struct octet_string M, struct octet_string P, int emLen)
{

    struct octet_string EM;
    char outputBuffer[65];

    printf("The message string is: %s\n", M.str_pointer);
    
    unsigned char sha256hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256_context;
    SHA256_Init(&sha256_context);
    SHA256_Update(&sha256_context, M.str_pointer, M.str_len);
    SHA256_Final(sha256hash, &sha256_context);
    /*
    int i;
    for (i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        sprintf(outputBuffer + (i*2), "%02x", hash[i]);
    }
    outputBuffer[64] = '\0';
    */
    printf("sha256 output:\n");
    int i;
    for (i = 0; i < SHA256_DIGEST_LENGTH; i++)
        printf("%c", sha256hash[i]);
    printf("\n");

    EM.str_pointer = (char *) malloc(5);
    EM.str_len = 4;
    EM.num_octets = 1;
    EM.error_detected = 0;

    return EM;
}

#endif
