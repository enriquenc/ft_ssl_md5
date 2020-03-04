#pragma once
#include <ft_ssl_md5.h>

# define F(B, C, D) 			((B) & (C)) | (~(B) & (D))
# define G(B, C, D) 			((B) & (D)) | ((C) & ~(D))
# define H(B, C, D) 			(B) ^ (C) ^ (D)
# define I(B, C, D) 			(C) ^ (B | ~(D))

#define LEFT_ROTATE(x, c) ((x << c) | (x >> (32 - c)));

#define NEEDED_MODULO_BYTES (448 / 8)
#define DIV_BYTES (512 / 8)

#define CHUNK_LEN_BYTES (512 / 8)

#define A_INIT_VALUE 0x67452301; // 67452301h
#define B_INIT_VALUE 0xefcdab89; // EFCDAB89h
#define C_INIT_VALUE 0x98badcfe; // 98BADCFEh
#define D_INIT_VALUE 0x10325476; // 10325476h

// typedef struct s_md5_chunk {

// } t_md5_chunk;

// typedef struct s_md5 {
// 	uint8_t buf[]
// } t_md5;

typedef struct s_md5_result_vector {
	uint32_t a;
	uint32_t b;
	uint32_t c;
	uint32_t d;
} t_md5_result_vector;

typedef struct s_md5_cycle_variables {
	uint8_t i;
	uint32_t f;
	uint32_t g;
} t_md5_cycle_variables;