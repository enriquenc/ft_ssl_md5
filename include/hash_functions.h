/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_functions.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaslyan <tmaslyan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 00:11:44 by tmaslyan          #+#    #+#             */
/*   Updated: 2020/03/24 00:52:39 by tmaslyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_FUNCTIONS_H
# define HASH_FUNCTIONS_H

#include <libft.h>

/**
 * @brief Amount of hash functions in the program.
 * Should be updated always when add new algorithm to table.
 */
#define ALGORITHM_AMOUNT 5

/**
 * @brief The MD5 message-digest algorithm is a widely used hash function
 * producing a 128-bit hash value. Although MD5 was initially designed to
 * be used as a cryptographic hash function, it has been found to suffer
 * from extensive vulnerabilities. It can still be used as a checksum to
 * verify data integrity, but only against unintentional corruption. It
 * remains suitable for other non-cryptographic purposes, for example for
 *  determining the partition for a particular key in a partitioned database.
 *
 * @param dest_buf Destination buffer to store md5 message digest.
 * Should be at least 128-bit in length.
 *
 * @param message User message to be hashed.
 *
 * @return uint8_t* encrypted message in dest_buf
 */
uint8_t			*md5(uint8_t *dest_buf, uint8_t *message);

/**
 * @brief Secure Hash Algorithms - SHA-256.
 * SHA-256 is one of the successor hash functions to SHA-1
 * (collectively referred to as SHA-2), and is one of the strongest hash
 * functions available. SHA-256 is not much more complex to code than SHA-1,
 * and has not yet been compromised in any way. The 256-bit key makes it a
 * good partner-function for AES. It is defined in the NIST (National
 * Institute of Standards and Technology) standard ‘FIPS 180-4’.
 *
 * @param dest_buf Destination buffer to store md5 message digest.
 * Should be at least 256-bit in length.
 *
 * @param message User message to be hashed.
 *
 * @return uint8_t* encrypted message in dest_buf
 */
uint8_t			*sha256(uint8_t *dest_buf, uint8_t *message);

/**
 * @brief SHA-224 is defined in the exact same manner as SHA-256, with the
 * following two exceptions:
 *    - First, for SHA-224, the initial hash values ​​of eight 32-bit working
 * variables use different values.
 *    - Second, SHA-224 simply makes use of the first seven 32-bit words
 * in the SHA-256 result, discarding the remaining 32-bit words in
 * the SHA-256 result.
 *
 * @param dest_buf Destination buffer to store md5 message digest.
 * Should be at least 224-bit in length.
 *
 * @param message User message to be hashed.
 *
 * @return uint8_t* encrypted message in dest_buf
 */
uint8_t			*sha224(uint8_t *dest_buf, uint8_t *message);
uint8_t			*sha512(uint8_t *dest_buf, uint8_t *message);
uint8_t			*sha384(uint8_t *dest_buf, uint8_t *message);


#endif