/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha384.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaslyan <tmaslyan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/23 00:46:53 by tmaslyan          #+#    #+#             */
/*   Updated: 2020/03/28 00:04:18 by tmaslyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sha384.h>

static void		vector_init_default(t_sha64b_vector *dest)
{
	dest->h0 = SHA384_H0_INIT_VALUE;
	dest->h1 = SHA384_H1_INIT_VALUE;
	dest->h2 = SHA384_H2_INIT_VALUE;
	dest->h3 = SHA384_H3_INIT_VALUE;
	dest->h4 = SHA384_H4_INIT_VALUE;
	dest->h5 = SHA384_H5_INIT_VALUE;
	dest->h6 = SHA384_H6_INIT_VALUE;
	dest->h7 = SHA384_H7_INIT_VALUE;
}

uint8_t			*sha384(uint8_t *dest_buf, uint8_t *message)
{
	t_sha64b_vector result_vector;

	vector_init_default(&result_vector);
	sha64b(message, &result_vector);
	ft_memcpy(dest_buf, &result_vector, sizeof(t_sha64b_vector) - sizeof(uint64_t));
	return dest_buf;
}