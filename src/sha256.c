/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaslyan <tmaslyan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 14:33:44 by tmaslyan          #+#    #+#             */
/*   Updated: 2020/03/07 22:35:50 by tmaslyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <sha2.h>
#include <sha256.h>
#include <md5.h>

#define SHA256_BLOCK_SIZE 32

static uint32_t g_current_chunk;

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

extern uint8_t g_padding;

void				md5_message_padding_append(t_ssl *message_data);


void				sha256_message_length_append(t_ssl *message_data)
{
	uint64_t bits_len;

	bits_len = 8 * message_data->message_len;
	bits_len = swap_int64(bits_len);
	memcpy(message_data->message + message_data->message_len +
						message_data->padding_len, &bits_len, 8);
	message_data->full_message_len_bytes = message_data->message_len
								+ message_data->padding_len + 8;
}


// static const uint32_t g_sha_2_constant[64] = {
// 	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1,
// 	0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
// 	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786,
// 	0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
// 	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
// 	0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
// 	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b,
// 	0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
// 	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a,
// 	0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
// 	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
// };

t_sha256_result_vector	sha256_vector_init_default(void)
{
	t_sha256_result_vector init;

	init.h0 = SHA256_H0_INIT_VALUE;
	init.h1 = SHA256_H1_INIT_VALUE;
	init.h2 = SHA256_H2_INIT_VALUE;
	init.h3 = SHA256_H3_INIT_VALUE;
	init.h4 = SHA256_H4_INIT_VALUE;
	init.h5 = SHA256_H5_INIT_VALUE;
	init.h6 = SHA256_H6_INIT_VALUE;
	init.h7 = SHA256_H7_INIT_VALUE;

	return init;
}

void			init_ssl_structure(t_ssl *message_data, uint8_t *message);

size_t	sha256(uint8_t *dest_buf, uint8_t *message)
{
	t_sha256_result_vector result_vector;
	uint32_t *chunk;
	t_ssl				message_data;
	ft_printf("sha256: non implemented yet.\n");

	init_ssl_structure(&message_data, message);
	md5_message_padding_append(&message_data);
	sha256_message_length_append(&message_data);
	result_vector = sha256_vector_init_default();
	chunk = NULL;
	g_current_chunk = 0;

	//while ((chunk))
	(void )dest_buf;

	for (size_t i = 0; i < message_data.full_message_len_bytes; i++) {
		ft_printf("%02x", message_data.message[i]);
		if (!((i + 1) % 4))
			ft_putchar(' ');
	}
	return (message_data.message_len);
}


#if 0


// typedef struct {
// 	uint8_t data[64];
// 	uint32_t datalen;
// 	unsigned long long bitlen;
// 	uint32_t state[8];
// } SHA256_CTX;



/*********************** FUNCTION DEFINITIONS ***********************/
void sha256_transform(SHA256_CTX *ctx, const uint8_t data[])
{
	uint32_t a, b, c, d, e, f, g, h, i, j, t1, t2, m[64];

	for (i = 0, j = 0; i < 16; ++i, j += 4)
		m[i] = (data[j] << 24) | (data[j + 1] << 16) | (data[j + 2] << 8) | (data[j + 3]);
	for ( ; i < 64; ++i)
		m[i] = SIG1(m[i - 2]) + m[i - 7] + SIG0(m[i - 15]) + m[i - 16];

	a = ctx->state[0];
	b = ctx->state[1];
	c = ctx->state[2];
	d = ctx->state[3];
	e = ctx->state[4];
	f = ctx->state[5];
	g = ctx->state[6];
	h = ctx->state[7];

	for (i = 0; i < 64; ++i) {
		t1 = h + EP1(e) + CH(e,f,g) + k[i] + m[i];
		t2 = EP0(a) + MAJ(a,b,c);
		h = g;
		g = f;
		f = e;
		e = d + t1;
		d = c;
		c = b;
		b = a;
		a = t1 + t2;
	}

	ctx->state[0] += a;
	ctx->state[1] += b;
	ctx->state[2] += c;
	ctx->state[3] += d;
	ctx->state[4] += e;
	ctx->state[5] += f;
	ctx->state[6] += g;
	ctx->state[7] += h;
}

void sha256_init(SHA256_CTX *ctx)
{
	ctx->datalen = 0;
	ctx->bitlen = 0;
	ctx->state[0] = 0x6a09e667;
	ctx->state[1] = 0xbb67ae85;
	ctx->state[2] = 0x3c6ef372;
	ctx->state[3] = 0xa54ff53a;
	ctx->state[4] = 0x510e527f;
	ctx->state[5] = 0x9b05688c;
	ctx->state[6] = 0x1f83d9ab;
	ctx->state[7] = 0x5be0cd19;
}

void sha256_update(SHA256_CTX *ctx, const uint8_t data[], size_t len)
{
	uint32_t i;

	for (i = 0; i < len; ++i) {
		ctx->data[ctx->datalen] = data[i];
		ctx->datalen++;
		if (ctx->datalen == 64) {
			sha256_transform(ctx, ctx->data);
			ctx->bitlen += 512;
			ctx->datalen = 0;
		}
	}
}

void sha256_final(SHA256_CTX *ctx, uint8_t hash[])
{
	uint32_t i;

	i = ctx->datalen;

	// Pad whatever data is left in the buffer.
	if (ctx->datalen < 56) {
		ctx->data[i++] = 0x80;
		while (i < 56)
			ctx->data[i++] = 0x00;
	}
	else {
		ctx->data[i++] = 0x80;
		while (i < 64)
			ctx->data[i++] = 0x00;
		sha256_transform(ctx, ctx->data);
		memset(ctx->data, 0, 56);
	}

	// Append to the padding the total message's length in bits and transform.
	ctx->bitlen += ctx->datalen * 8;
	ctx->data[63] = ctx->bitlen;
	ctx->data[62] = ctx->bitlen >> 8;
	ctx->data[61] = ctx->bitlen >> 16;
	ctx->data[60] = ctx->bitlen >> 24;
	ctx->data[59] = ctx->bitlen >> 32;
	ctx->data[58] = ctx->bitlen >> 40;
	ctx->data[57] = ctx->bitlen >> 48;
	ctx->data[56] = ctx->bitlen >> 56;
	sha256_transform(ctx, ctx->data);

	// Since this implementation uses little endian uint8_t ordering and SHA uses big endian,
	// reverse all the uint8_ts when copying the final state to the output hash.
	for (i = 0; i < 4; ++i) {
		hash[i]      = (ctx->state[0] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 4]  = (ctx->state[1] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 8]  = (ctx->state[2] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 12] = (ctx->state[3] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 16] = (ctx->state[4] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 20] = (ctx->state[5] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 24] = (ctx->state[6] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 28] = (ctx->state[7] >> (24 - i * 8)) & 0x000000ff;
	}
}


#endif
