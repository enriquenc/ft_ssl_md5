#pragma once
#include <ft_ssl_md5.h>

#define F(X, Y, Z) = (X & Y) | (~X & Z) /* first round */
#define G(X, Y, Z) = (X & Z) | (Y & ~Z) /* second round */
#define H(X, Y, Z) = X ^ Y ^ Z /* third round */
#define I(X, Y, Z) = Y ^ (X & ~Z) /* fourth round */

#define NEEDED_MODULO_BYTES 448 / 8
#define DIV_BYTES 512 / 8

size_t md5(t_ssl *message_data);

// typedef struct s_md5 {
// 	uint8_t buf[]
// } t_md5;
