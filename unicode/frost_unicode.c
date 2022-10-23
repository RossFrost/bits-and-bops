#include "unicode.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


static inline char *u_character_p(UNICODE_STRING *u_string, size_t pos) {
    return u_string->u_string[pos].character;
};

static inline size_t sizeof_u_character_p(UNICODE_STRING *u_string, size_t pos) {
    return u_string->u_string[pos].size;
};

enum FROST_UNICODE_ERROR create_u_string(UNICODE_STRING *u_string) {
    if (u_string->num_characters > strlen(u_string->map)) {
        return ERR_LENGTH_OUT_OF_BOUNDS;
    }

    size_t current_byte = 0;

    UNICODE_CHARACTER *u_array = calloc(u_string->num_characters + 1, sizeof(UNICODE_CHARACTER));

    for (size_t i_character = 0; i_character < u_string->num_characters; ++i_character) {
        char u_bytesize = u_string->map[i_character];
        u_array[i_character].character = calloc(u_bytesize, 1); 
        strncpy(u_array[i_character].character, u_string->bytes + current_byte, u_bytesize);

        u_array[i_character].size = u_bytesize;
        u_array[i_character].position = i_character;

        current_byte += u_bytesize;
    }

    u_string->u_string = u_array;
}


enum FROST_UNICODE_ERROR init_u_string(char *string, UNICODE_STRING *u_string) {
    size_t length_in_bytes = strnlen(string, __INT32_MAX__);

    if (length_in_bytes == __UINT32_MAX__) {
        return ERR_NO_LINE_TERMINATOR;
    }

    char *unicode_character_sizes = calloc(sizeof(char), 1);
    int size = 0;
    
    for (int i_byte = 0; i_byte < length_in_bytes; i_byte) {
        ++size;

        if (size == INT_MAX) {
            return ERR_TOO_MANY_CHARACTERS;
        }

        char iteration = 0;
        char byte = string[i_byte];
        char mask = 1 << 7;

        for (char i_bit = 0; i_bit != 8; ++i_bit) {
            if (byte & mask) {
                ++iteration;
                byte = byte << 1;
                continue;
            } else if (i_bit == 0) {
                ++iteration;
                break;
            } else {
                break;
            }
        }

        i_byte += iteration;
        unicode_character_sizes = realloc(unicode_character_sizes, (size_t)(size + 1));
        unicode_character_sizes[size - 1] = iteration;
    }

    
        u_string->map = unicode_character_sizes;
        u_string->num_characters = size;
        u_string->bytes = string;

        return UNICODE_SUCESS;
}
