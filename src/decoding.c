#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include <inttypes.h>

#include "group.h"
#include "decoding.h"

void decode_to_source_octet(const char* input, size_t input_size, const struct source_octets* source);

size_t decode(const char* input, char** output) {
    const size_t input_size = strlen(input);

    struct source_group encoded_octets[input_size / 4];
    const struct source_octets decode = {
            .size = input_size / 4,
            .groups = encoded_octets,
            .has_additional = false,
    };

    uint8_t paddings_count = 0;
    for(size_t i = input_size; i-- > 0; ) {
        if(input[i] == '=') paddings_count++;
        else break;
    }
    const size_t output_size = (input_size * 6 / 8) - paddings_count + 1;

    decode_to_source_octet(input, input_size, &decode);

    char* out = (char*)malloc(sizeof(char) * output_size);
    size_t temp_c = 0;
    for(size_t i = 0; i < output_size; ) {
        union source_group_raw graw  = { .sg =  decode.groups[temp_c] }; // todo: try without copy
        for(size_t j = 0; j < 3; j++) {
            if(graw.raw[j] != 0) {
                out[i] = (char) graw.raw[j];
                i++;
            } else {
                out[i] = '\0';
                goto end_decoding;
            }
        }
        temp_c++;
    }
    end_decoding:

    *output = out;

    return output_size - 1; // without zero char
}

void decode_to_source_octet(const char* input, size_t input_size, const struct source_octets* source) {
    size_t temp_c = 0;
    for(size_t i = 0; (i + 4) <= input_size; i += 4) {
        const uint32_t hex = ( ((uint32_t)alphabet_decode[(size_t)input[i + 0]] & 0x3F) << 18 )
                             | ( ((uint32_t)alphabet_decode[(size_t)input[i + 1]] & 0x3F ) << 12 )
                             | ( ((uint32_t)alphabet_decode[(size_t)input[i + 2]] & 0x3F ) << 6 )
                             | ( ((uint32_t)alphabet_decode[(size_t)input[i + 3]] & 0x3F ) << 0 );

        source->groups[temp_c].octet1 = (uint8_t)((hex >> 16) & 0xFF);
        source->groups[temp_c].octet2 = (uint8_t)((hex >> 8) & 0xFF);
        source->groups[temp_c].octet3 = (uint8_t)((hex) & 0xFF);

        temp_c++;
    }
}
