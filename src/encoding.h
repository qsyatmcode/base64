#ifndef BASE64_ENCODING_H
#define BASE64_ENCODING_H

#include "alphabet.h"
#include "group.h"

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>

struct encoded_octets* read_octets(const char* input);

#endif //BASE64_ENCODING_H
