#include <stdint.h>
#include <string.h>
#include <malloc.h>

#include "encoding.h"
#include "group.h"

void read_octets(const char* input, struct source_octets* source);
static struct group encode_source_octet(const struct source_group* sg);

size_t encode(const char* input, char** output) {
    if(!input) return 0;

    const size_t input_len = strlen(input);
    const size_t full_groups_count = input_len / 3;
    const size_t source_size = input_len % 3 != 0 ? full_groups_count + 1 : full_groups_count;

    struct source_group s[source_size];
    struct source_octets source = {
            .size = source_size,
            .has_additional = input_len % 3 != 0,
            .groups = s,
    };

    read_octets(input, &source);

    struct group encoded_groups[source_size];
    struct encoded_octets encoded = {
            .size = source.size,
            .groups = encoded_groups,
    };

    for(size_t i = 0; i < source.size; i++) {
        encoded.groups[i] = encode_source_octet(&source.groups[i]);
    }

    //const bool add_zerochar = encoded.groups[encoded.size - 1].sextet4 != 0;
    const size_t result_size = sizeof(char) * (encoded.size * 4 + 1);
    char* result = (char*) malloc( result_size );
    if(!result) return 0;

    size_t offset = 0;
    for(size_t i = 0; i < encoded.size; i++) {
        result[i + offset++] = alphabet_encode[encoded.groups[i].sextet1 ? encoded.groups[i].sextet1 : ALBT_PADDING];
        result[i + offset++] = alphabet_encode[encoded.groups[i].sextet2 ? encoded.groups[i].sextet2 : ALBT_PADDING];
        result[i + offset++] = alphabet_encode[encoded.groups[i].sextet3 ? encoded.groups[i].sextet3 : ALBT_PADDING];
        result[i + offset] = alphabet_encode[encoded.groups[i].sextet4 ? encoded.groups[i].sextet4 : ALBT_PADDING];
    }

    result[result_size - 1] = '\0';

    *output = result;

    return result_size;
}

void read_octets(const char* input, struct source_octets* source) {
    //get_source_group(input, source);
    const size_t input_len = strlen(input);
    const char* const limit = input + input_len;
    const char* it = input;

    size_t gcount = 0;
    while(gcount < (source->size - source->has_additional)) {
        uint8_t octet1 = *(it++);
        uint8_t octet2 = *(it++);
        uint8_t octet3 = *(it++);

        source->groups[gcount] = (struct source_group) {octet1, octet2, octet3, };
        gcount++;
    }

    if(source->has_additional) {
        union source_group_raw last_group;
        uint8_t fields_count = 0;
        while (it <= limit) {
            last_group.raw[fields_count] = *(it++);
            fields_count++;
        }
        while (fields_count < 3) {
            last_group.raw[fields_count] = 0;
            fields_count++;
        }
        source->groups[gcount] = last_group.sg;
    }
}

static struct group encode_source_octet(const struct source_group* sg) {
    const uint32_t hex = ( (uint32_t)sg->octet1 << 16 ) | ( (uint32_t)sg->octet2 << 8 ) | ( (uint32_t)sg->octet3 );

    struct sextet {
        uint8_t n: 6;
    } oct[4];

    for(uint8_t i = 0; i < 4; i++) oct[i].n = (hex >> (6 * i)) & 0x3F;

    // 0x0 if is padding (0x3D)
    return (struct group) {
        .sextet1 = oct[3].n, // ? oct[3].n : 0x3D,
        .sextet2 = oct[2].n, // ? oct[2].n : 0x3D,
        .sextet3 = oct[1].n, // ? oct[1].n : 0x3D,
        .sextet4 = oct[0].n, // ? oct[0].n : 0x3D,
    };
}
