/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha2.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaslyan <tmaslyan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 17:51:00 by tmaslyan          #+#    #+#             */
/*   Updated: 2020/03/28 00:16:09 by tmaslyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** This header include common part for SHA2 hash algorithms.
*/

#ifndef SHA2_H
# define SHA2_H

# include <my_openssl.h>

/**
 * @brief SHA-2 common binary opearations
 */
# define CH(x, y, z) (((x) & (y)) ^ (~(x) & (z)))
# define MAJ(x, y, z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))

/**
 * @brief 32bit vector used to compute and store the intermediate hash value.
 */
typedef struct	__attribute__ ((packed))	s_sha32b_vector {
	uint32_t h0;
	uint32_t h1;
	uint32_t h2;
	uint32_t h3;
	uint32_t h4;
	uint32_t h5;
	uint32_t h6;
	uint32_t h7;
}											t_sha32b_vector;

/**
 * @brief Like t_sha32b_vector but with 64bit data type.
 */
typedef struct	__attribute__ ((packed))	s_sha64b_vector  {
	uint64_t h0;
	uint64_t h1;
	uint64_t h2;
	uint64_t h3;
	uint64_t h4;
	uint64_t h5;
	uint64_t h6;
	uint64_t h7;
}											t_sha64b_vector;

/**
 * @brief Used to store values of main sha2 cycle.
 * This shit exists to satisfy the Norminette.
 */
typedef struct		s_sha32b_main_cycle {
	uint8_t		i;
	uint32_t	w[64];
	uint32_t	temp1;
	uint32_t	temp2;
}					t_sha32b_main_cycle;

/**
 * @brief Like t_sha32b_main_cycle but with 64bit data type.
 */
typedef struct		s_sha64b_main_cycle {
	uint8_t		i;
	uint64_t	w[80];
	uint64_t	temp1;
	uint64_t	temp2;
}					t_sha64b_main_cycle;

/**
 * @brief Main calculation of sha2 for 32bit type algorithms.
 * @param message User message to be hashed.
 * @param result_vector vector with calculated values.
 */
void	sha32b(uint8_t *message, t_sha32b_vector *result_vector);

/**
 * @brief Main calculation of sha2 for 64bit type algorithms.
 * @param message User message to be hashed.
 * @param result_vector vector with calculated values.
 */
void	sha64b(uint8_t *message, t_sha64b_vector *result_vector);
#endif
