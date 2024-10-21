#ifndef BASE64_DECODING_H
#define BASE64_DECODING_H

#include <stddef.h>
#include "alphabet.h"

size_t decode(const char* input, char** output);

#endif //BASE64_DECODING_H
