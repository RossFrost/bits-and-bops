enum FROST_UNICODE_ERROR {
    UNICODE_SUCESS,
    ERR_ZERO_BYTE_CHARACTER,
    ERR_NO_LINE_TERMINATOR,
    ERR_STRING_TO_LONG,
    ERR_UNICODE_CHARACTER_TOO_BIG,
    ERR_TOO_MANY_CHARACTERS,
    ERR_INVALID_POSITION,
    ERR_LENGTH_OUT_OF_BOUNDS,
    ENCOUNTER_NULL_CHARACTER,

};

typedef struct {
    char *character;
    char size;
    unsigned long long position;
} UNICODE_CHARACTER;

typedef struct {
    char *bytes;
    UNICODE_CHARACTER *u_string;
    unsigned long long num_characters;
    char *map;
} UNICODE_STRING;


enum FROST_UNICODE_ERROR init_u_string(char *string, UNICODE_STRING *u_string);
enum FROST_UNICODE_ERROR create_u_string(UNICODE_STRING *u_string);
static inline char *u_character_p(UNICODE_STRING *u_string, unsigned long long pos);
static inline unsigned long long sizeof_u_character_p(UNICODE_STRING *u_string, unsigned long long pos);
