#ifndef BASE64_ENCODING_H
#define BASE64_ENCODING_H

#include <inttypes.h>
#include <stddef.h>

size_t encode(const char* input, char** output);

#endif //BASE64_ENCODING_H
