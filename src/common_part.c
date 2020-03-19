/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_part.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaslyan <tmaslyan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 00:58:36 by tmaslyan          #+#    #+#             */
/*   Updated: 2020/03/19 23:42:48 by tmaslyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <connector.h>

/*
** Array used to append padding to the message,
** Starts from 1 bit (ASCII 128(dec) / 0x80(hex)) and ends
** by n 0 bits according to the message:
** (len_in_bits(message) % 512 == 488)
*/

uint8_t g_padding[64] = {
	0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

uint32_t		swap_int32(const uint32_t value)
{
	uint32_t result;

	result = 0;
	result |= (value & 0x000000FF) << 24;
	result |= (value & 0x0000FF00) << 8;
	result |= (value & 0x00FF0000) >> 8;
	result |= (value & 0xFF000000) >> 24;
	return (result);
}

uint64_t		swap_int64(const uint64_t val)
{
	return ((((val) & 0xff00000000000000ull) >> 56) |
			(((val) & 0x00ff000000000000ull) >> 40) |
			(((val) & 0x0000ff0000000000ull) >> 24) |
			(((val) & 0x000000ff00000000ull) >> 8) |
			(((val) & 0x00000000ff000000ull) << 8) |
			(((val) & 0x0000000000ff0000ull) << 24) |
			(((val) & 0x000000000000ff00ull) << 40) |
			(((val) & 0x00000000000000ffull) << 56));
}

void				init_ssl_structure(t_ssl *message_data, uint8_t *msg)
{
	message_data->current_chunk = 0;
	message_data->chunk = NULL;
	message_data->message_len = ft_strlen((const char *)msg);
	ft_memcpy(message_data->message, msg, message_data->message_len + 1);
}

void				message_padding_append(t_ssl *message_data)
{
	message_data->padding_len = 0;
	while ((++message_data->padding_len + message_data->message_len)
								% DIV_BYTES != NEEDED_MODULO_BYTES)
		;
	ft_memcpy(message_data->message + message_data->message_len,
							g_padding, message_data->padding_len);
}

uint32_t			*get_current_chunk(t_ssl *message_data,
											uint8_t chunk_len_bytes)
{
	uint32_t *chunk;

	if (message_data->current_chunk >= message_data->full_message_len_bytes
											/ chunk_len_bytes)
		return (NULL);
	chunk = (uint32_t *)(message_data->message +
						(message_data->current_chunk * chunk_len_bytes));
	message_data->current_chunk++;
	return (chunk);
}

void				message_length_append(t_ssl *message_data,
												uint64_t bits_len)
{
	memcpy(message_data->message + message_data->message_len +
						message_data->padding_len, &bits_len, 8);
	message_data->full_message_len_bytes = message_data->message_len
								+ message_data->padding_len + 8;
}
