/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connector.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaslyan <tmaslyan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 14:35:45 by tmaslyan          #+#    #+#             */
/*   Updated: 2020/03/07 22:44:21 by tmaslyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONNECTOR_H
# define CONNECTOR_H

# include <ft_ssl_md5.h>

typedef enum	e_error {
	USAGE,
	INVALID_COMMAND,
	INVALID_OPTION,
	EXPECTED_ARGUMENT,
}				t_error;

typedef struct	s_algorithm {
	char				name[24];
	t_hash_algorithm	num;
	t_hash_func			func;
	uint8_t				digest_len_bytes;
}				t_algorithm;

typedef struct	s_parser_data {
	uint8_t				options;
	char				*s_option_data[MAX_STRING_ARGUMENT_COUNT];
	char				*files_data[MAX_FILE_ARGUMENT_COUNT];
	t_algorithm			algorithm;
}				t_parser_data;

size_t			md5(uint8_t *dest_buf, uint8_t *message);
void			connector(t_parser_data *message_data);
void			ft_ssl_error(t_error code, void *arg);
size_t			sha256(uint8_t *dest_buf, uint8_t *message);
t_parser_data	parser(int argc, char **argv);

#endif
