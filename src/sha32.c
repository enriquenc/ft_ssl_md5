/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha32.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaslyan <tmaslyan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/22 14:05:17 by tmaslyan          #+#    #+#             */
/*   Updated: 2020/03/22 18:13:58 by tmaslyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sha2.h>

static void	vector_add(t_sha32b_vector *dest, t_sha32b_vector *src)
{
	dest->h0 += src->h0;
	dest->h1 += src->h1;
	dest->h2 += src->h2;
	dest->h3 += src->h3;
	dest->h4 += src->h4;
	dest->h5 += src->h5;
	dest->h6 += src->h6;
	dest->h7 += src->h7;
}

static void	sub_cycle(t_sha2_main_cycle *cycle, t_sha32b_vector *calc_vector)
{
	cycle->i = 0;
	while (cycle->i < 64)
	{
		cycle->temp1 = calc_vector->h7 + BSIG1(calc_vector->h4) +
			CH(calc_vector->h4, calc_vector->h5, calc_vector->h6) +
			 g_precalculated_table[cycle->i] + cycle->w[cycle->i];
		cycle->temp2 = BSIG0(calc_vector->h0) + MAJ(calc_vector->h0,
			calc_vector->h1, calc_vector->h2);
		calc_vector->h7 = calc_vector->h6;
		calc_vector->h6 = calc_vector->h5;
		calc_vector->h5 = calc_vector->h4;
		calc_vector->h4 = calc_vector->h3 + cycle->temp1;
		calc_vector->h3 = calc_vector->h2;
		calc_vector->h2 = calc_vector->h1;
		calc_vector->h1 = calc_vector->h0;
		calc_vector->h0 = cycle->temp1 + cycle->temp2;
		cycle->i++;
	}
}

static void	main_cycle(t_ssl *msg_data, t_sha32b_vector *result_vector,
			t_sha32b_vector *calc_vector)
{
	t_sha2_main_cycle cycle;

	while ((msg_data->chunk = get_current_chunk(msg_data,
									SHA2_CHUNK_LEN_BYTES)))
	{
		cycle.i = -1;
		while (++cycle.i < 16)
			cycle.w[cycle.i] = swap_int32(msg_data->chunk[cycle.i]);
		while (cycle.i < 64)
		{
			cycle.w[cycle.i] = SSIG1(cycle.w[cycle.i - 2]) +
				cycle.w[cycle.i - 7] + SSIG0(cycle.w[cycle.i - 15]) +
				cycle.w[cycle.i - 16];
			cycle.i++;
		}
		memcpy(calc_vector, result_vector, sizeof(t_sha32b_vector));
		sub_cycle(&cycle, calc_vector);
		vector_add(result_vector, calc_vector);
	}
}

void		sha32b(uint8_t *message, t_sha32b_vector *result_vector)
{
	t_sha32b_vector		calc_vector;
	t_ssl				msg_data;
	int					i;

	init_ssl_structure(&msg_data, message);
	message_padding_append(&msg_data);
	message_length_append(&msg_data, swap_int64(msg_data.message_len * 8));
	main_cycle(&msg_data, result_vector, &calc_vector);
	i = -1;
	while (++i < 8)
		*(((uint32_t *)result_vector) + i) =
					swap_int32(*(((uint32_t *)result_vector) + i));
}
