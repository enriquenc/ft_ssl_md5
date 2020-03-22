/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha2.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaslyan <tmaslyan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 17:51:00 by tmaslyan          #+#    #+#             */
/*   Updated: 2020/03/22 18:15:00 by tmaslyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** This header include parts of code for SHA‑256, SHA‑224
** hash algorithms
*/

#ifndef SHA2_H
# define SHA2_H

# include <ft_ssl_md5.h>

# define CH(x, y, z) (((x) & (y)) ^ (~(x) & (z)))
# define MAJ(x, y, z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
# define BSIG0(x) (RIGHT_ROTATE(x, 2) ^ RIGHT_ROTATE(x, 13) ^ RIGHT_ROTATE(x, 22))
# define BSIG1(x) (RIGHT_ROTATE(x, 6) ^ RIGHT_ROTATE(x, 11) ^ RIGHT_ROTATE(x, 25))
# define SSIG0(x) (RIGHT_ROTATE(x, 7) ^ RIGHT_ROTATE(x, 18) ^ ((x) >> 3))
# define SSIG1(x) (RIGHT_ROTATE(x, 17) ^ RIGHT_ROTATE(x, 19) ^ ((x) >> 10))

# define SHA2_CHUNK_LEN_BYTES (512 / 8)

typedef struct		s_sha32b_vector {
	uint32_t h0;
	uint32_t h1;
	uint32_t h2;
	uint32_t h3;
	uint32_t h4;
	uint32_t h5;
	uint32_t h6;
	uint32_t h7;
}					t_sha32b_vector;

typedef struct		s_sha2_main_cycle {
	uint8_t		i;
	uint32_t	w[64];
	uint32_t	temp1;
	uint32_t	temp2;
}					t_sha2_main_cycle;

static const uint32_t g_precalculated_table[64] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b,
	0x59f111f1, 0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01,
	0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7,
	0xc19bf174, 0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
	0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da, 0x983e5152,
	0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
	0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc,
	0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819,
	0xd6990624, 0xf40e3585, 0x106aa070, 0x19a4c116, 0x1e376c08,
	0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f,
	0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

void	sha32b(uint8_t *message, t_sha32b_vector *result_vector);

#endif
