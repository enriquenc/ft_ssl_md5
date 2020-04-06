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

/**
 * @brief Realization of the programm flags to use only 1 byte of memory.
 */
# define FLAG_P (1 << 0)
# define FLAG_Q (1 << 1)
# define FLAG_R (1 << 2)
# define FLAG_S (1 << 3)

/**
 * @brief Global error codes.
 */
typedef enum	e_error {
	USAGE,
	INVALID_COMMAND,
	INVALID_OPTION,
	EXPECTED_ARGUMENT,
}				t_error;

/**
 * @brief Main structure of parser which store all necessary data
 * after extraction.
 */
typedef struct	s_parser_data {
	uint8_t				options; /* store all inputed flags */
	char				*s_option_data[MAX_STRING_ARGUMENT_COUNT]; /* store all strings for -s flag */
	char				*files_data[MAX_FILE_ARGUMENT_COUNT]; /* store all inputed filenames */
	t_algorithm			algorithm; /* store the infromation of choosen algorithm */
}				t_parser_data;

/**
 * @brief This function executes all that was requested by the user using
 * parsed data from message_data object. It takes into account all the
 * arguments and flags that were entered by the user.
 * @param message_data parsed input data.
 */
void			connector(t_parser_data *message_data);

/**
 * @brief Used to handle all the errors.
 * @param code Error code.
 * @param arg Some argument to display (optional).
 */
void			ft_ssl_error(t_error code, void *arg);

/**
 * @brief Parses the input arguments of the program into the
 * appropriate structure - t_parser_data.
 *
 * @param argc Arguments count.
 * @param argv Arguments array.
 * @return t_parser_data parsed data.
 */
t_parser_data	parser(int argc, char **argv);

/**
 * @brief Gets all the file content from any file by name.
 *
 * @param dest Buffer. !ATTENTION! Use buffer with enough size!
 * @param file_name File name.
 * @return uint8_t Error code.
 */
uint8_t			get_file_content(uint8_t *dest, char *file_name);

/**
 * @brief Reads all the the data from any descriptor.
 *
 * @param dest Buffer. !ATTENTION! Use buffer with enough size!
 * @param fd File descriptor.
 */
void			read_from_descriptor(uint8_t *dest, int fd);

extern t_algorithm g_algorithms[ALGORITHM_AMOUNT];

#endif
