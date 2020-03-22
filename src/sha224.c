/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha224.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaslyan <tmaslyan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/22 13:35:10 by tmaslyan          #+#    #+#             */
/*   Updated: 2020/03/22 18:13:58 by tmaslyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sha2.h>
#include <sha224.h>

static void		sha224_vector_init_default(t_sha32b_vector *dest)
{
	dest->h0 = SHA224_H0_INIT_VALUE;
	dest->h1 = SHA224_H1_INIT_VALUE;
	dest->h2 = SHA224_H2_INIT_VALUE;
	dest->h3 = SHA224_H3_INIT_VALUE;
	dest->h4 = SHA224_H4_INIT_VALUE;
	dest->h5 = SHA224_H5_INIT_VALUE;
	dest->h6 = SHA224_H6_INIT_VALUE;
	dest->h7 = SHA224_H7_INIT_VALUE;
}

uint8_t	*sha224(uint8_t *dest_buf, uint8_t *message)
{
	t_sha32b_vector result_vector;

	sha224_vector_init_default(&result_vector);
	sha32b(message, &result_vector);
	ft_memcpy(dest_buf, &result_vector, sizeof(t_sha32b_vector) - sizeof(uint32_t));
	return dest_buf;
}