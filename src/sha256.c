/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaslyan <tmaslyan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 14:33:44 by tmaslyan          #+#    #+#             */
/*   Updated: 2020/03/19 23:52:05 by tmaslyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <sha2.h>
#include <sha256.h>
#include <connector.h>

#define SHA256_BLOCK_SIZE 32

/*TODO поменять копирование векторов на memcpy*/


static const uint32_t g_K[64] = {
 0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b,
 0x59f111f1, 0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01,
 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7,
 0xc19bf174, 0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da, 0x983e5152,
 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
 0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc,
 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
 0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819,
 0xd6990624, 0xf40e3585, 0x106aa070, 0x19a4c116, 0x1e376c08,
 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f,
 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

void	sha256_vector_init_default(t_sha256_result_vector *dest)
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

void sha256_vector_add(t_sha256_result_vector *dest,
										t_sha256_result_vector *src)
{
	dest->h0 += src->h0; // a
	dest->h1 += src->h1; // b
	dest->h2 += src->h2; // c
	dest->h3 += src->h3; // d
	dest->h4 += src->h4; // e
	dest->h5 += src->h5; // f
	dest->h6 += src->h6; // g
	dest->h7 += src->h7; // h
}

void sha2_vector_calculation(t_sha256_result_vector *calc_vector, uint32_t T1, uint32_t T2) {
	calc_vector->h7 = calc_vector->h6;
	calc_vector->h6 = calc_vector->h5;
	calc_vector->h5 = calc_vector->h4;
	calc_vector->h4 = calc_vector->h3 + T1;
	calc_vector->h3 = calc_vector->h2;
	calc_vector->h2 = calc_vector->h1;
	calc_vector->h1 = calc_vector->h0;
	calc_vector->h0 = T1 + T2;
}

void sha2_main_cycle(t_ssl *msg_data, t_sha256_result_vector *result_vector, t_sha256_result_vector *calc_vector)
{
	uint8_t		i;
	uint32_t	W[64];
	uint32_t	T1;
	uint32_t	T2;

	while ((msg_data->chunk = get_current_chunk(msg_data,
									SHA2_CHUNK_LEN_BYTES)))
	{
		i = -1;
		while (++i < 16)
			W[i] = swap_int32(msg_data->chunk[i]);
		while (i < 64) {
			W[i] = SSIG1(W[i - 2]) + W[i - 7] + SSIG0(W[i - 15]) + W[i - 16];
			i++;
		}
		memcpy(calc_vector, result_vector, sizeof(t_sha256_result_vector));
		i = 0;
		while (i < 64) {
			T1 = calc_vector->h7 + BSIG1(calc_vector->h4) + CH(calc_vector->h4, calc_vector->h5, calc_vector->h6) + g_K[i] + W[i];
			T2 = BSIG0(calc_vector->h0) + MAJ(calc_vector->h0, calc_vector->h1, calc_vector->h2);
			sha2_vector_calculation(calc_vector, T1, T2);
			i++;
		}
		sha256_vector_add(result_vector, calc_vector);
	}
}

uint8_t	*sha256(uint8_t *dest_buf, uint8_t *message)
{
	t_sha256_result_vector	result_vector;
	t_sha256_result_vector	calc_vector;
	t_ssl					msg_data;
	uint32_t				*res_vec_ptr;

	init_ssl_structure(&msg_data, message);
	message_padding_append(&msg_data);
	message_length_append(&msg_data, swap_int64(msg_data.message_len * 8));
	sha256_vector_init_default(&result_vector);
	sha2_main_cycle(&msg_data, &result_vector, &calc_vector);
	res_vec_ptr = (uint32_t *)&result_vector;
	for (int i = 0; i < 8; i++) {
		*(res_vec_ptr + i) = swap_int32(*(res_vec_ptr + i));
	}
	ft_memcpy(dest_buf, &result_vector, sizeof(t_sha256_result_vector));
	return (dest_buf);
}
