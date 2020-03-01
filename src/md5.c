#include <md5.h>

static uint8_t s[64] = {7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,
5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,
4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,
6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21 };


/* Array used to append padding to the message,
* Starts from 1 bit (ASCII 128(dec) / 0x80(hex)) and ends
* by n 0 bits according to the message:
* (len_in_bits(message) % 512 == 488)
*/

static uint8_t PADDING[64] = {
  0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

/* Binary integer part of the sines of integers (Radians) as constants:
 * for(int i = 0; i < 64; i++)
 *    TABLE[i] = (int)(pow(2, 32) × abs(sin(i + 1)))
 * (I just use the following precomputed table)
*/

static uint32_t TABLE[64] = {
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

void md5_message_padding_append(t_ssl *message_data) {
	message_data->padding_len = 0; /* count of symbols to add */
	while ((++message_data->padding_len + message_data->message_len) % DIV_BYTES != NEEDED_MODULO_BYTES);
	ft_memcpy(message_data->message + message_data->message_len, PADDING, message_data->padding_len);
}

void md5_message_length_append(t_ssl *message_data) {
	uint64_t bits_len = 8 * message_data->message_len;
	memcpy(message_data->message + message_data->message_len + message_data->padding_len, &bits_len, 8);
}

uint32_t *md5_get_current_chunk(t_ssl *message_data) {
	static uint8_t current_chunk;

	if (current_chunk >= message_data->full_message_len_bytes / CHUNK_LEN_BYTES)
		return NULL;

	uint32_t *chunk = (uint32_t *)(message_data->message + current_chunk * CHUNK_LEN_BYTES);
	current_chunk++;

	return chunk;
}

size_t md5(t_ssl *message_data) {
	//char buf[MAX_BUFFER_SIZE];

	// size_t arg_len = 0;
	// if (*(argv + 1))
	// 	arg_len = ft_strlen(*(argv + 1));

	//int len = ft_atoi((const char *)message_data->message);
	message_data->message_len = ft_strlen((const char *)message_data->message);
	// for (size_t i = 0; i < message_data->message_len; i++)
	// 	ft_printf("%d", (unsigned)message_data->message[i]);
	// ft_putchar('\n');
	md5_message_padding_append(message_data);
	md5_message_length_append(message_data);
	// for (size_t i = 0; i < message_data->message_len + message_data->padding_len + 8; i++)
	// 	ft_printf("%d", (unsigned)message_data->message[i]);
	// ft_putchar('\n');

	uint32_t a0 = A_INIT_VALUE;
	uint32_t b0 = B_INIT_VALUE;
	uint32_t c0 = C_INIT_VALUE;
	uint32_t d0 = D_INIT_VALUE;
	//(len);
	message_data->full_message_len_bytes = message_data->message_len + message_data->padding_len + 8;
	// ft_printf("%d", message_data->full_message_len_bytes);
	// uint8_t chunk_number = 0;
	uint32_t *chunk = NULL;

	while ((chunk = md5_get_current_chunk(message_data))) {
		uint32_t A = a0;
		uint32_t B = b0;
		uint32_t C = c0;
		uint32_t D = d0;

		int i = 0;
		while (i < 64) {
			uint32_t f, g;
			if (i < 16) {
				f = F(B, C, D);
				g = i;
			} else if (i < 32) {
				f = G(B, C, D);
				g = (5 * i + 1) % 16;
			} else if (i < 48) {
				f = H(B, C, D);
				g = (3 * i + 5) % 16;
			} else if (i < 64) {
				f = I(B, C, D);
				g = (7 * i) % 16;
			}
			f = f + A + TABLE[i] + *(chunk + g);
			A = D;
			D = C;
			C = B;
			B = B + LEFT_ROTATE(f, s[i]);
			i++;
		}
		a0 += A;
		b0 += B;
		c0 += C;
		d0 += D;
	}
	uint8_t result[16];
	ft_memcpy(result, &a0, 4);
	ft_memcpy(result + 4, &b0, 4);
	ft_memcpy(result + 8, &c0, 4);
	ft_memcpy(result + 12, &d0, 4);

	for (int i = 0; i < 16; i++) {
		ft_printf("%02x", result[i]);
	}
	ft_putchar('\n');
	return 0;
}
