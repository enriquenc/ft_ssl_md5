/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_openssl.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaslyan <tmaslyan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 14:35:49 by tmaslyan          #+#    #+#             */
/*   Updated: 2020/04/20 23:44:30 by tmaslyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_OPENSSL_H
# define MY_OPENSSL_H

# include <libft.h>

/**
 * @brief Max buffer size in the main structure in the project to copy,
 * append padding and length of the message.
 */
# define MAX_BUFFER_SIZE 1267920 * 2
# define MAX_STRING_ARGUMENT_COUNT 32
# define MAX_FILE_ARGUMENT_COUNT 32

/**
 * @brief Different defines to make left and right rotate
 * with different data types.
 */
# define LROTATE32(a, b) (((a) << (b)) | ((a) >> (32 - (b))))
# define RROTATE32(a, b) (((a) >> (b)) | ((a) << (32 - (b))))
# define RROTATE64(a, b) (((a) >> (b)) | ((a) << (64 - (b))))

/**
 * @brief Defines of different chunk length and modulo length in bytes
 * to make correct padding and save place for appending length
 */
# define CHUNK512_MODULO (448 / 8)
# define CHUNK512_LEN (512 / 8)
# define CHUNK1024_MODULO (896 / 8)
# define CHUNK1024_LEN (1024 / 8)

/**
 * @brief Pointer to the hash function.
 * Used to add piece of polymorphism and avoid lot of checks.
 */
typedef uint8_t *	(*t_hash_func)(uint8_t *dest_buf, uint8_t *message);

/**
 * @brief Used in t_ssl structure to add chunks support with
 * different pointer type without type cast.
 */
typedef union	chunk
{
	uint32_t	*chunk32;
	uint64_t	*chunk64;
}				t_chunk;

/**
 * @brief Main structure of the project.
 *
 * Contain all necessary information about current message to encrypt.
 */
typedef struct	s_ssl {
	uint8_t		message[MAX_BUFFER_SIZE]; /* buffer which */
	uint32_t	current_chunk; /* current chunk of the message buffer*/
	t_chunk		chunk;  /* pointer to the chunk in the the message
						   accordance to the hash algorithm chunk type. */
	size_t		message_len; /* length of the start message (before padding) */
	size_t		padding_len; /* length of padding (without message_len) */
	size_t		full_message_len_bytes; /* message length after padding
										and length append in bytes */
}				t_ssl;

/**
 * @brief Describe each of hash algorithms.
 * Helps to provide abstraction with finding and outputing of the hash.
 */
typedef struct	s_algorithm {
	char				name[24]; /* name of algorithm */
	t_hash_func			hash_function; /* pointer to the appropriate hash function */
	uint8_t				hash_size_bytes; /* size of result hash in bytes */
	uint16_t			options_mask; /* bit field with algorithm options */
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
