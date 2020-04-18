/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaslyan <tmaslyan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/23 22:25:48 by tmaslyan          #+#    #+#             */
/*   Updated: 2020/03/24 00:09:03 by tmaslyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <my_openssl.h>

uint32_t		swap_int32(const uint32_t value)
{
	return (((value & 0x000000FF) << 24) |
			((value & 0x0000FF00) << 8) |
			((value & 0x00FF0000) >> 8) |
			((value & 0xFF000000) >> 24));
}

uint64_t		swap_int64(const uint64_t value)
{
	return (((uint64_t)swap_int32(value) << 32) | swap_int32(value >> 32));
}

uint128_t		swap_int128(const uint128_t value)
{
	return (((uint128_t)swap_int64(value) << 64) | swap_int64(value >> 64));
}

