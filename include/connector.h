#pragma once
#include <ft_ssl_md5.h>

typedef struct s_hash_functions {
	hash_func func;
} t_hash_functions;

typedef enum e_error {
	USAGE,
	INVALID_COMMAND,
	INVALID_OPTION,
	EXPECTED_ARGUMENT,
} t_error;

typedef struct s_algorithms {
	char name[24];
	t_hash_algorithm alg;
} t_algorithms;


size_t md5(t_ssl *message_data);
void connector(t_parser_data *message_data);
void ft_ssl_error(t_error code, void *arg);
size_t sha256(t_ssl *message_data);