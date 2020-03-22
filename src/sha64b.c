/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha64b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaslyan <tmaslyan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/22 18:12:18 by tmaslyan          #+#    #+#             */
/*   Updated: 2020/03/22 20:52:04 by tmaslyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sha2.h>

# define RROTATE(a, b) (((a) >> (b)) | ((a) << (64 - (b))))

# define BSIG0(x) (RROTATE(x, 28) ^ RROTATE(x, 34) ^ RROTATE(x, 39))
# define BSIG1(x) (RROTATE(x, 14) ^ RROTATE(x, 18) ^ RROTATE(x, 41))
# define SSIG0(x) (RROTATE(x, 1) ^ RROTATE(x, 8) ^ ((x) >> 7))
# define SSIG1(x) (RROTATE(x, 19) ^ RROTATE(x, 61) ^ ((x) >> 6))

static const uint64_t g_precalculated_table[80] = {
	0x428a2f98d728ae22, 0x7137449123ef65cd, 0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc,
	0x3956c25bf348b538, 0x59f111f1b605d019, 0x923f82a4af194f9b, 0xab1c5ed5da6d8118,
	0xd807aa98a3030242, 0x12835b0145706fbe, 0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2,
	0x72be5d74f27b896f, 0x80deb1fe3b1696b1, 0x9bdc06a725c71235, 0xc19bf174cf692694,
	0xe49b69c19ef14ad2, 0xefbe4786384f25e3, 0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65,
	0x2de92c6f592b0275, 0x4a7484aa6ea6e483, 0x5cb0a9dcbd41fbd4, 0x76f988da831153b5,
	0x983e5152ee66dfab, 0xa831c66d2db43210, 0xb00327c898fb213f, 0xbf597fc7beef0ee4,
	0xc6e00bf33da88fc2, 0xd5a79147930aa725, 0x06ca6351e003826f, 0x142929670a0e6e70,
	0x27b70a8546d22ffc, 0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed, 0x53380d139d95b3df,
	0x650a73548baf63de, 0x766a0abb3c77b2a8, 0x81c2c92e47edaee6, 0x92722c851482353b,
	0xa2bfe8a14cf10364, 0xa81a664bbc423001, 0xc24b8b70d0f89791, 0xc76c51a30654be30,
	0xd192e819d6ef5218, 0xd69906245565a910, 0xf40e35855771202a, 0x106aa07032bbd1b8,
	0x19a4c116b8d2d0c8, 0x1e376c085141ab53, 0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8,
	0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb, 0x5b9cca4f7763e373, 0x682e6ff3d6b2b8a3,
	0x748f82ee5defb2fc, 0x78a5636f43172f60, 0x84c87814a1f0ab72, 0x8cc702081a6439ec,
	0x90befffa23631e28, 0xa4506cebde82bde9, 0xbef9a3f7b2c67915, 0xc67178f2e372532b,
	0xca273eceea26619c, 0xd186b8c721c0c207, 0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178,
	0x06f067aa72176fba, 0x0a637dc5a2c898a6, 0x113f9804bef90dae, 0x1b710b35131c471b,
	0x28db77f523047d84, 0x32caab7b40c72493, 0x3c9ebe0a15c9bebc, 0x431d67c49c100d4c,
	0x4cc5d4becb3e42b6, 0x597f299cfc657e2a, 0x5fcb6fab3ad6faec, 0x6c44198c4a475817,
};

static void	vector_add(t_sha64b_vector *dest, t_sha64b_vector *src)
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

static void	sub_cycle(t_sha64b_main_cycle *cycle, t_sha64b_vector *calc_vector)
{
	cycle->i = 0;
	while (cycle->i < 80)
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

static void	main_cycle(t_ssl *msg_data, t_sha64b_vector *result_vector,
			t_sha64b_vector *calc_vector)
{
	t_sha64b_main_cycle cycle;

	while ((msg_data->chunk.chunk64b = (uint64_t *)get_current_chunk(msg_data,
									SHA64B_CHUNK_LEN_BYTES)))
	{
		cycle.i = -1;
		while (++cycle.i < 16)
			cycle.w[cycle.i] = swap_int64(msg_data->chunk.chunk64b[cycle.i]);
		while (cycle.i < 80)
		{
			cycle.w[cycle.i] = SSIG1(cycle.w[cycle.i - 2]) +
				cycle.w[cycle.i - 7] + SSIG0(cycle.w[cycle.i - 15]) +
				cycle.w[cycle.i - 16];
			cycle.i++;
		}
		memcpy(calc_vector, result_vector, sizeof(t_sha64b_vector));
		sub_cycle(&cycle, calc_vector);
		vector_add(result_vector, calc_vector);
	}
}

void		sha64b(uint8_t *message, t_sha64b_vector *result_vector)
{
	t_sha64b_vector		calc_vector;
	t_ssl				msg_data;
	size_t					i;

	init_ssl_structure(&msg_data, message);
	message_padding_append(&msg_data, CHUNK1024_MODULO, CHUNK1024_LEN);
	message_length_append(&msg_data, swap_int128(msg_data.message_len * 8), sizeof(uint128_t));
	main_cycle(&msg_data, result_vector, &calc_vector);
	i = -1;
	while (++i < 8)
		*(((uint64_t *)result_vector) + i) =
					swap_int64(*(((uint64_t *)result_vector) + i));
}
