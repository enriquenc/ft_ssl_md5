/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connector.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaslyan <tmaslyan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 14:35:45 by tmaslyan          #+#    #+#             */
/*   Updated: 2020/03/07 19:51:35 by tmaslyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONNECTOR_H
# define CONNECTOR_H

# include <ft_ssl_md5.h>

typedef struct	s_hash_functions {
	t_hash_func func;
}				t_hash_functions;

typedef enum	e_error {
	USAGE,
	INVALID_COMMAND,
	INVALID_OPTION,
	EXPECTED_ARGUMENT,
}				t_error;

typedef struct	s_algorithms {
	char				name[24];
	t_hash_algorithm	alg;
}				t_algorithms;

size_t			md5(uint8_t *message);
void			connector(t_parser_data *message_data);
void			ft_ssl_error(t_error code, void *arg);
size_t			sha256(uint8_t *message);
t_parser_data	parser(int argc, char **argv);

#endif
