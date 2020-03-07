/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_md5.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaslyan <tmaslyan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 14:35:49 by tmaslyan          #+#    #+#             */
/*   Updated: 2020/03/07 15:56:23 by tmaslyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_MD5_H
# define FT_SSL_MD5_H

# include "libft.h"

# define MAX_BUFFER_SIZE 1267920 * 2
# define MAX_STRING_ARGUMENT_COUNT 32
# define MAX_FILE_ARGUMENT_COUNT 32

# define FLAG_P (1 << 0)
# define FLAG_Q (1 << 1)
# define FLAG_R (1 << 2)
# define FLAG_S (1 << 3)

typedef enum	e_hash_algorithm {
	MD5,
	SHA256,
	MAX
}				t_hash_algorithm;

typedef struct	s_ssl {
	uint8_t		message[MAX_BUFFER_SIZE];
	size_t		message_len;
	size_t		padding_len;
	size_t		full_message_len_bytes;
}				t_ssl;

typedef struct	s_parser_data {
	t_hash_algorithm	algorithm;
	uint8_t				options;
	char				*s_option_data[MAX_STRING_ARGUMENT_COUNT];
	char				*files_data[MAX_FILE_ARGUMENT_COUNT];
}				t_parser_data;

typedef size_t	(*t_hash_func)(t_ssl *message_data);

#endif
