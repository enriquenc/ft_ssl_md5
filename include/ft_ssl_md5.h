#pragma once
#include "libft.h"

#define MAX_BUFFER_SIZE 1267920 * 2
#define MAX_STRING_ARGUMENT_COUNT 32
#define MAX_FILE_ARGUMENT_COUNT 32

#define FLAG_P (1 << 0)
#define FLAG_Q (1 << 1)
#define FLAG_R (1 << 2)
#define FLAG_S (1 << 3)

typedef __uint8_t uint8_t;
typedef __uint16_t uint16_t;
typedef __uint32_t uint32_t;
typedef __uint64_t uint64_t;

// probably move to different logic segment
typedef enum e_hash_algorithm {
	MD5,
	SHA256,
	MAX
} t_hash_algorithm;

typedef struct s_ssl {
	uint8_t message[MAX_BUFFER_SIZE];
	size_t message_len;
	size_t padding_len;
	size_t full_message_len_bytes;
} t_ssl;

typedef struct s_parser_data {
	t_hash_algorithm algorithm;
	uint8_t options;
	char *s_option_data[MAX_STRING_ARGUMENT_COUNT];
	char *files_data[MAX_FILE_ARGUMENT_COUNT];
} t_parser_data;

typedef size_t (* hash_func)(t_ssl *message_data);
