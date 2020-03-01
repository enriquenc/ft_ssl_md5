#pragma once
#include <ft_ssl_md5.h>

typedef struct s_hash_functions {
	hash_func func;
} t_hash_functions;


size_t md5(t_ssl *message_data);
void connector(t_ssl *message_data);
