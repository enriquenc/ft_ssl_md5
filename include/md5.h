/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaslyan <tmaslyan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 14:35:53 by tmaslyan          #+#    #+#             */
/*   Updated: 2020/03/08 01:03:16 by tmaslyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_H
# define MD5_H
# include <ft_ssl_md5.h>

# define F(B, C, D) ((B) & (C)) | (~(B) & (D))
# define G(B, C, D) ((B) & (D)) | ((C) & ~(D))
# define H(B, C, D) (B) ^ (C) ^ (D)
# define I(B, C, D) (C) ^ (B | ~(D))

# define A_INIT_VALUE 0x67452301;
# define B_INIT_VALUE 0xefcdab89;
# define C_INIT_VALUE 0x98badcfe;
# define D_INIT_VALUE 0x10325476;

typedef struct		s_md5_result_vector {
	uint32_t a;
	uint32_t b;
	uint32_t c;
	uint32_t d;
}					t_md5_result_vector;

typedef struct		s_md5_cycle_variables {
	uint8_t		i;
	uint32_t	f;
	uint32_t	g;
}					t_md5_cycle_variables;

t_md5_result_vector	md5_vector_add(t_md5_result_vector dest,
										t_md5_result_vector src);
t_md5_result_vector	md5_vector_copy(t_md5_result_vector dest,
										t_md5_result_vector src);
t_md5_result_vector	md5_vector_init_default();
void				md5_rounds(t_md5_cycle_variables *var,
								t_md5_result_vector calc_vector);

#endif
