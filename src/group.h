#ifndef BASE64_GROUP_H
#define BASE64_GROUP_H

#include <stdint.h>
#include <stdbool.h>

//#include "alphabet.h"

struct group {
    uint8_t sextet1:6;
    uint8_t sextet2:6;
    uint8_t sextet3:6;
    uint8_t sextet4:6;
};

struct source_group {
    uint8_t octet1;
    uint8_t octet2;
    uint8_t octet3;
};

union source_group_raw {
    struct source_group sg;
    uint8_t raw[3];
};

struct source_octets {
    const size_t size;
    const bool has_additional;
    struct source_group* groups;
};

struct encoded_octets {
    const size_t size;
    struct group* groups;
};

#endif //BASE64_GROUP_H
