#ifndef BASE64_ENCODING_H
#define BASE64_ENCODING_H

#include <stddef.h>
#include "alphabet.h"

size_t encode(const char* input, char** output);

#endif //BASE64_ENCODING_H
