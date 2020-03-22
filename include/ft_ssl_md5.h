/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_md5.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaslyan <tmaslyan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 14:35:49 by tmaslyan          #+#    #+#             */
/*   Updated: 2020/03/23 01:07:39 by tmaslyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_MD5_H
# define FT_SSL_MD5_H

# include "libft.h"

# define MAX_BUFFER_SIZE 1267920 * 2
# define MAX_STRING_ARGUMENT_COUNT 32
# define MAX_FILE_ARGUMENT_COUNT 32

# define LEFT_ROTATE(a, b) (((a) << (b)) | ((a) >> (32 - (b))))

# define CHUNK512_MODULO (448 / 8)
# define CHUNK512_LEN (512 / 8)
# define CHUNK1024_MODULO (896 / 8)
# define CHUNK1024_LEN (1024 / 8)

# define FLAG_P (1 << 0)
# define FLAG_Q (1 << 1)
# define FLAG_R (1 << 2)
# define FLAG_S (1 << 3)

#ifdef __linux__
typedef u_int8_t uint8_t;
typedef u_int32_t uint32_t;
typedef u_int64_t uint64_t;
typedef __int128_t uint128_t;

#endif

typedef uint8_t *	(*t_hash_func)(uint8_t *dest_buf, uint8_t *message);

typedef enum	e_hash_algorithm {
	MD5,
	SHA256,
	SHA224,
	SHA512,
	SHA384,
	MAX
}				t_hash_algorithm;

typedef union	chunk
{
	uint32_t	*chunk32b;
	uint64_t	*chunk64b;
}				t_chunk;

typedef struct	s_ssl {
	uint8_t		message[MAX_BUFFER_SIZE];
	uint32_t	current_chunk;
	t_chunk		chunk;
	size_t		message_len;
	size_t		padding_len;
	size_t		full_message_len_bytes;
}				t_ssl;

typedef struct	s_algorithm {
	char				name[24];
	t_hash_algorithm	num;
	t_hash_func			func;
	uint8_t				hash_size_bytes;
}				t_algorithm;




void			message_padding_append(t_ssl *message_data,
							uint8_t modulo, uint8_t need_chunk_length);
void			message_length_append(t_ssl *message_data,
											uint128_t bits_len, uint8_t size);
uint32_t		swap_int32(const uint32_t value);
uint64_t		swap_int64(const uint64_t val);
uint128_t		swap_int128(const uint128_t val);

void			*get_current_chunk(t_ssl *message_data,
											uint8_t chunk_len_bytes);
void			init_ssl_structure(t_ssl *message_data, uint8_t *message);

#endif
