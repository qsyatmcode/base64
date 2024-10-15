#include <stdio.h>
#include <inttypes.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "encoding.h"

#define INPUT_BUFFER_SIZE 32

size_t read_string(char* input_buffer, size_t buffer_size);

int main(void) {
    char input_buffer[INPUT_BUFFER_SIZE];


    if (!read_string(input_buffer, INPUT_BUFFER_SIZE)) {
        printf("Reading is failed");
        return EXIT_FAILURE;
    }

    read_octets(input_buffer);

    printf("%s", input_buffer);

    return EXIT_SUCCESS;
}

size_t read_string(char* input_buffer, size_t buffer_size) {
    size_t read = 0;
    if(!input_buffer) return read;

    char *const limit = input_buffer + buffer_size;

    int ch = 0;
    char *it = input_buffer;
    while ((ch = getchar()) != EOF && ch != '\n' && it != limit) {
        *(it++) = (char) ch;
        read++;
    }

    *it = '\0';

    return read;
}
