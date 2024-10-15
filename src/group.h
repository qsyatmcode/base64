#ifndef BASE64_GROUP_H
#define BASE64_GROUP_H

#include <stdint.h>

/*
   struct group gr = {
    4010:	01 01                	add    DWORD PTR [rcx],eax
    4012:	01 01                	add    DWORD PTR [rcx],eax
*/

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

#endif //BASE64_GROUP_H
