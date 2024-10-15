#include "encoding.h"

struct source_octets {
    const size_t size;
    const bool has_additional;
    struct source_group* groups;
};

struct encoded_octets {
    const size_t size;
    struct group* groups;
};


static void get_source_group(const char* input, struct source_octets* source);
static struct group encode_source_octet(const struct source_group* sg);

static void debug_source_octets_print(const struct source_octets* source);


struct encoded_octets* read_octets(const char* input) {
    if(!input) return NULL;

    const size_t input_len = strlen(input);
    const size_t full_groups_count = input_len / 3;
    const size_t source_size = input_len % 3 != 0 ? full_groups_count + 1 : full_groups_count;

    struct source_group s[source_size];
    struct source_octets source = {
        .size = source_size,
        .has_additional = input_len % 3 != 0,
        .groups = s,
    };

    get_source_group(input, &source);

    debug_source_octets_print(&source);

    for(size_t i = 0; i < source.size; i++) {
        struct group d = encode_source_octet(&source.groups[i]);
        //printf("%c, ", (unsigned char)d.sextet1);
        //printf("%c, ", (unsigned char)d.sextet2);
        //printf("%c, ", (unsigned char)d.sextet3);
        //printf("%c;\n", (unsigned char)d.sextet4);
    }

    return NULL;
}


// Returns size of groups
static void get_source_group(const char* input, struct source_octets* source) {
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
    uint32_t hex = ( (uint32_t)sg->octet1 << 16 ) | ( (uint32_t)sg->octet2 << 8 ) | ( (uint32_t)sg->octet3 );

    struct sextet {
        uint8_t n: 6;
    } oct[4];

    for(uint8_t i = 0; i < 4; i++) oct[i].n = (hex >> (6 * i)) & 0x3F;

    // 0x0 if padding
    return (struct group) {
        .sextet1 = oct[3].n,
        .sextet2 = oct[2].n,
        .sextet3 = oct[1].n,
        .sextet4 = oct[0].n,
    };
}


static void debug_source_octets_print(const struct source_octets* source) {
    printf("Size: %zu\n", source->size);
    for(size_t i = 0; i < source->size; i++) {
        printf("Oktet %zu: ", i);
        printf("%c, ", (char)source->groups[i].octet1);
        printf("%c, ", (char)source->groups[i].octet2);
        printf("%c;\n", (char)source->groups[i].octet3);
    }
}
