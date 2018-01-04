#ifndef HASH_H
#define HASH_H

#include <openssl/sha.h>

int generate_sha_256_hash(void* hash_source, unsigned long source_length, unsigned char* md);

int generate_sha_256_hash(void* hash_source, unsigned long source_length, unsigned char* md)
{
    int i = 0;

    SHA256_CTX context;
    if (!SHA256_Init(&context))
        return 0;

    if (!SHA256_Update(&context, (unsigned char *) hash_source, source_length))
        return 0;

    if (!SHA256_Final(md, &context))
        return 0;

    for (i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        printf("%02X", md[i]);
    }

    return 1;
}

#endif
