/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaslyan <tmaslyan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 14:35:53 by tmaslyan          #+#    #+#             */
/*   Updated: 2020/03/28 00:14:15 by tmaslyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_H
# define MD5_H
# include <my_openssl.h>

# define F(B, C, D) ((B) & (C)) | (~(B) & (D))
# define G(B, C, D) ((B) & (D)) | ((C) & ~(D))
# define H(B, C, D) (B) ^ (C) ^ (D)
# define I(B, C, D) (C) ^ (B | ~(D))

# define A_INIT_VALUE 0x67452301;
# define B_INIT_VALUE 0xefcdab89;
# define C_INIT_VALUE 0x98badcfe;
# define D_INIT_VALUE 0x10325476;

/**
 * @brief 32bit vector used to compute and store the intermediate hash value.
 */
typedef struct	__attribute__ ((packed))	s_md5_result_vector {
	uint32_t a;
	uint32_t b;
	uint32_t c;
	uint32_t d;
}											t_md5_vector;

/**
 * @brief Used to store values of main md5 cycle.
 * This shit exists to satisfy the Norminette.
 */
typedef struct		s_md5_cycle_variables {
	uint8_t		i;
	uint32_t	f;
	uint32_t	g;
}					t_md5_cycle;

#endif
