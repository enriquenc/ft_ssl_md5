/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha2.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaslyan <tmaslyan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 17:51:00 by tmaslyan          #+#    #+#             */
/*   Updated: 2020/03/24 00:09:03 by tmaslyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** This header include parts of code for SHA‑256, SHA‑224
** hash algorithms
*/

#ifndef SHA2_H
# define SHA2_H

# include <my_openssl.h>

# define CH(x, y, z) (((x) & (y)) ^ (~(x) & (z)))
# define MAJ(x, y, z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))

# define SHA32B_CHUNK_LEN_BYTES (CHUNK512_LEN)
# define SHA64B_CHUNK_LEN_BYTES (CHUNK1024_LEN)

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

typedef struct		s_sha64b_vector {
	uint64_t h0;
	uint64_t h1;
	uint64_t h2;
	uint64_t h3;
	uint64_t h4;
	uint64_t h5;
	uint64_t h6;
	uint64_t h7;
}					t_sha64b_vector;

typedef struct		s_sha32b_main_cycle {
	uint8_t		i;
	uint32_t	w[64];
	uint32_t	temp1;
	uint32_t	temp2;
}					t_sha32b_main_cycle;

typedef struct		s_sha64b_main_cycle {
	uint8_t		i;
	uint64_t	w[80];
	uint64_t	temp1;
	uint64_t	temp2;
}					t_sha64b_main_cycle;

void	sha32b(uint8_t *message, t_sha32b_vector *result_vector);
void	sha64b(uint8_t *message, t_sha64b_vector *result_vector);
#endif
