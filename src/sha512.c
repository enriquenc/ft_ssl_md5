/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaslyan <tmaslyan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/22 18:57:26 by tmaslyan          #+#    #+#             */
/*   Updated: 2020/03/22 19:07:29 by tmaslyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sha2.h>
#include <sha512.h>

static void		vector_init_default(t_sha64b_vector *dest)
{
	dest->h0 = SHA512_H0_INIT_VALUE;
	dest->h1 = SHA512_H1_INIT_VALUE;
	dest->h2 = SHA512_H2_INIT_VALUE;
	dest->h3 = SHA512_H3_INIT_VALUE;
	dest->h4 = SHA512_H4_INIT_VALUE;
	dest->h5 = SHA512_H5_INIT_VALUE;
	dest->h6 = SHA512_H6_INIT_VALUE;
	dest->h7 = SHA512_H7_INIT_VALUE;
}

uint8_t	*sha512(uint8_t *dest_buf, uint8_t *message)
{
	t_sha64b_vector result_vector;

	vector_init_default(&result_vector);
	sha64b(message, &result_vector);
	ft_memcpy(dest_buf, &result_vector, sizeof(t_sha64b_vector));
	return dest_buf;
}