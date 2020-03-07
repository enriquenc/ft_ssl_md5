/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaslyan <tmaslyan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 14:33:08 by tmaslyan          #+#    #+#             */
/*   Updated: 2020/03/08 01:08:18 by tmaslyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <md5.h>
#include <connector.h>

static uint8_t g_s[64] = {
	7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
	5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
	4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
	6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
};

/*
** Binary integer part of the sines of integers (Radians) as constants:
** for(int i = 0; i < 64; i++)
**    TABLE[i] = (int)(pow(2, 32) × abs(sin(i + 1)))
** (I just use the following precomputed table)
*/

static uint32_t g_table[64] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391,
};

void				md5_message_length_append(t_ssl *message_data)
{
	uint64_t bits_len;

	bits_len = 8 * message_data->message_len;
	memcpy(message_data->message + message_data->message_len +
						message_data->padding_len, &bits_len, 8);
	message_data->full_message_len_bytes = message_data->message_len
								+ message_data->padding_len + 8;
}

t_md5_result_vector	md5_cycle_calculation(uint32_t *chunk,
							t_md5_result_vector calc_vector)
{
	t_md5_cycle_variables var;

	var.i = 0;
	while (var.i < 64)
	{
		md5_rounds(&var, calc_vector);
		var.f = var.f + calc_vector.a + g_table[var.i] + *(chunk + var.g);
		calc_vector.a = calc_vector.d;
		calc_vector.d = calc_vector.c;
		calc_vector.c = calc_vector.b;
		calc_vector.b = calc_vector.b + LEFT_ROTATE(var.f, g_s[var.i]);
		var.i++;
	}
	return (calc_vector);
}

uint32_t			*md5_get_current_chunk(t_ssl *message_data)
{
	uint32_t *chunk;

	if (message_data->current_chunk >= message_data->full_message_len_bytes
											/ CHUNK_LEN_BYTES)
		return (NULL);
	chunk = (uint32_t *)(message_data->message +
						(message_data->current_chunk * CHUNK_LEN_BYTES));
	message_data->current_chunk++;
	return (chunk);
}

size_t				md5(uint8_t *dest_buf, uint8_t *message)
{
	t_md5_result_vector	result_vector;
	t_md5_result_vector	calc_vector;
	t_ssl				message_data;

	init_ssl_structure(&message_data, message);
	message_padding_append(&message_data);
	md5_message_length_append(&message_data);
	result_vector = md5_vector_init_default();
	while ((message_data.chunk = md5_get_current_chunk(&message_data)))
	{
		calc_vector = md5_vector_copy(calc_vector, result_vector);
		calc_vector = md5_cycle_calculation(message_data.chunk, calc_vector);
		result_vector = md5_vector_add(result_vector, calc_vector);
	}
	ft_memcpy(dest_buf, &result_vector, 16);
	return (0);
}
