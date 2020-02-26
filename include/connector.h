#pragma once
#include <md5.h>

typedef struct s_hash_functions {
	hash_func func;
} t_hash_functions;


void connector(t_ssl *message_data);
