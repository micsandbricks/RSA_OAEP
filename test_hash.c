#ifndef TEST_HASH_H
#define TEST_HASH_H

#include <stdio.h>
#include "openssl/sha.h"
#include "hash.h"

int main()
{
    int i;
    unsigned char md[SHA256_DIGEST_LENGTH];
    char* input_string = "hakuna matata!";
    int len = 14;

    if (!generate_sha_256_hash(input_string, 14, md))
    {
        printf("Error when generating hash");
    }
}

#endif
