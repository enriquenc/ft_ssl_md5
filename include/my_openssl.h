/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_openssl.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaslyan <tmaslyan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 14:35:49 by tmaslyan          #+#    #+#             */
/*   Updated: 2020/03/24 00:15:25 by tmaslyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_OPENSSL_H
# define MY_OPENSSL_H

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

typedef uint8_t *	(*t_hash_func)(uint8_t *dest_buf, uint8_t *message);

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

/**
 * @brief Structure which describe each of hash algorithms.
 */
typedef struct	s_algorithm {
	char				name[24]; /* name of algorithm */
	t_hash_func			func;
	uint8_t				hash_size_bytes;
}				t_algorithm;


/**
 * @brief Initialization of the main structure of the project.
 * Copying message to the buffer in this structure with appropriate size.
 *
 * @param message_data main structure of the project which includes all
 * required data about input message and actually the message.
 *
 * @param message initial message which come to us from user.
 */
void			init_ssl_structure(t_ssl *message_data, uint8_t *message);

/**
 * @brief Append padding to the message before it is input to the hash function
 *
 * @param message_data main structure of the project which includes all
 * required data about input message and actually the message.
 *
 * @param modulo actually, this value is (need_chunk_bytes - sizeof(msg_len))
 * We just save the place for future append of length of the message.
 *
 * @param need_chunk_length length of the message should be the multiple of
 * this value after padding.
 */
void			message_padding_append(t_ssl *message_data,
							uint8_t modulo, uint8_t need_chunk_length);

/**
 * @brief Append length of the message to the end of message.
 *
 * @param message_data main structure of the project which includes all
 * required data about input message and actually the message.
 *
 * @param bits_len length of the message in bits.
 *
 * @param size sizeof(msg_len) 32/64/128 bytes.
 */
void			message_length_append(t_ssl *message_data,
											uint128_t bits_len, uint8_t size);

/**
 * @brief Get the current chunk of the message.
 *
 * @param message_data main structure of the project which includes all
 * required data about input message and actually the message.
 *
 * @param chunk_len_bytes length of the chunk to get.
 *
 * @return void* pointer to the current chunk with undefined data type.
 * Developer can cast this pointer to the appropriate type.
 */
void			*get_current_chunk(t_ssl *message_data,
													uint8_t chunk_len_bytes);

/**
 * @brief Swap bytes in the 32bit value.
 *
 * @param value source value to be changed.
 * @return value with swapped bytes.
 */
uint32_t		swap_int32(const uint32_t value);

/**
 * @brief Swap bytes in the 64bit value.
 *
 * @param value source value to be changed.
 * @return value with swapped bytes.
 */
uint64_t		swap_int64(const uint64_t value);

/**
 * @brief Swap bytes in the 128bit value.
 *
 * @param value source value to be changed.
 * @return value with swapped bytes.
 */
uint128_t		swap_int128(const uint128_t value);

#endif
