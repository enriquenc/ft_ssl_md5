/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha2.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaslyan <tmaslyan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 17:51:00 by tmaslyan          #+#    #+#             */
/*   Updated: 2020/03/18 23:54:30 by tmaslyan         ###   ########.fr       */
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
