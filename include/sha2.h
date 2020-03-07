/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha2.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaslyan <tmaslyan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 17:51:00 by tmaslyan          #+#    #+#             */
/*   Updated: 2020/03/08 01:05:40 by tmaslyan         ###   ########.fr       */
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
# define BSIG0(x) (LEFT_ROTATE(x, 2) ^ LEFT_ROTATE(x, 13) ^ LEFT_ROTATE(x, 22))
# define BSIG1(x) (LEFT_ROTATE(x, 6) ^ LEFT_ROTATE(x, 11) ^ LEFT_ROTATE(x, 25))
# define SSIG0(x) (LEFT_ROTATE(x, 7) ^ LEFT_ROTATE(x, 18) ^ ((x) >> 3))
# define SSIG1(x) (LEFT_ROTATE(x, 17) ^ LEFT_ROTATE(x, 19) ^ ((x) >> 10))

# define SHA2_CHUNK_LEN_BYTES (512 / 8)

typedef struct		s_sha256_result_vector {
	uint32_t h0;
	uint32_t h1;
	uint32_t h2;
	uint32_t h3;
	uint32_t h4;
	uint32_t h5;
	uint32_t h6;
	uint32_t h7;
}					t_sha256_result_vector;

#endif
