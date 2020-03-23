/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaslyan <tmaslyan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 14:35:45 by tmaslyan          #+#    #+#             */
/*   Updated: 2020/03/19 23:43:49 by tmaslyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONNECTOR_H
# define CONNECTOR_H

# include <my_openssl.h>
# include <hash_functions.h>
# include <libft.h>

typedef enum	e_error {
	USAGE,
	INVALID_COMMAND,
	INVALID_OPTION,
	EXPECTED_ARGUMENT,
}				t_error;

typedef struct	s_parser_data {
	uint8_t				options;
	char				*s_option_data[MAX_STRING_ARGUMENT_COUNT];
	char				*files_data[MAX_FILE_ARGUMENT_COUNT];
	t_algorithm			algorithm;
}				t_parser_data;

void			connector(t_parser_data *message_data);
void			ft_ssl_error(t_error code, void *arg);
t_parser_data	parser(int argc, char **argv);
uint8_t			get_file_content(uint8_t *dest, char *file_name);
void			read_from_descriptor(uint8_t *dest, int fd);

extern t_algorithm g_algorithms[ALGORITHM_AMOUNT];

#endif
