/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaslyan <tmaslyan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 14:33:44 by tmaslyan          #+#    #+#             */
/*   Updated: 2020/03/28 00:04:26 by tmaslyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sha256.h>

static void		sha256_vector_init_default(t_sha32b_vector *dest)
{
	dest->h0 = SHA256_H0_INIT_VALUE;
	dest->h1 = SHA256_H1_INIT_VALUE;
	dest->h2 = SHA256_H2_INIT_VALUE;
	dest->h3 = SHA256_H3_INIT_VALUE;
	dest->h4 = SHA256_H4_INIT_VALUE;
	dest->h5 = SHA256_H5_INIT_VALUE;
	dest->h6 = SHA256_H6_INIT_VALUE;
	dest->h7 = SHA256_H7_INIT_VALUE;
}

uint8_t			*sha256(uint8_t *dest_buf, uint8_t *message)
{
	t_sha32b_vector	result_vector;

	sha256_vector_init_default(&result_vector);
	sha32b(message, &result_vector);
	ft_memcpy(dest_buf, &result_vector, sizeof(t_sha32b_vector));
	return dest_buf;
}
