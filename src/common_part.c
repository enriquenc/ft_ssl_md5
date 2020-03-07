/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_part.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaslyan <tmaslyan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 00:58:36 by tmaslyan          #+#    #+#             */
/*   Updated: 2020/03/08 01:07:52 by tmaslyan         ###   ########.fr       */
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

void				init_ssl_structure(t_ssl *message_data, uint8_t *msg)
{
	message_data->current_chunk = 0;
	message_data->chunk = NULL;
	ft_memcpy(message_data->message, msg, strlen((const char *)msg) + 1);
}

void				message_padding_append(t_ssl *message_data)
{
	message_data->message_len = ft_strlen((const char *)message_data->message);
	message_data->padding_len = 0;
	while ((++message_data->padding_len + message_data->message_len)
								% DIV_BYTES != NEEDED_MODULO_BYTES)
		;
	ft_memcpy(message_data->message + message_data->message_len,
							g_padding, message_data->padding_len);
}
