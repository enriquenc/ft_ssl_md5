#pragma once
#include "libft.h"

#define MAX_BUFFER_SIZE 1024


typedef __uint8_t uint8_t;
typedef __uint16_t uint16_t;
typedef __uint32_t uint32_t;
typedef __uint64_t uint64_t;

// probably move to different logic segment
typedef enum e_hash_algorithm {
	MD5,
	MAX
} t_hash_algorithm;

typedef struct s_ssl {
	uint8_t message[MAX_BUFFER_SIZE];
	t_hash_algorithm algorithm;
	size_t message_len;
} t_ssl;

typedef size_t (* hash_func)(t_ssl *message_data);
