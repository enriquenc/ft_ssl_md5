/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaslyan <tmaslyan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 14:52:47 by tmaslyan          #+#    #+#             */
/*   Updated: 2020/04/20 23:23:34 by tmaslyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

t_algorithm g_algorithms[ALGORITHM_AMOUNT] = {
#define DECLARE_COMMAND(_name, _func, _size, _opt_mask) {\
		.name = _name, \
		.hash_function = _func, \
		.hash_size_bytes = _size, \
		.options_mask = _opt_mask }

	DECLARE_COMMAND("md5", md5, 16, (FLAG_P | FLAG_Q | FLAG_R | FLAG_S)),
	DECLARE_COMMAND("sha256", sha256, 256 / 8, (FLAG_P | FLAG_Q | FLAG_R | FLAG_S)),
	DECLARE_COMMAND("sha224", sha224, 224 / 8, (FLAG_P | FLAG_Q | FLAG_R | FLAG_S)),
	DECLARE_COMMAND("sha512", sha512, 512 / 8, (FLAG_P | FLAG_Q | FLAG_R | FLAG_S)),
	DECLARE_COMMAND("sha384", sha384, 384 / 8, (FLAG_P | FLAG_Q | FLAG_R | FLAG_S))
};

t_flag g_flags[FLAGS_AMOUNT] = {
#define DECLARE_FLAG(_name, _mask, _description) {\
	.name = _name, \
	.mask = _mask, \
	.description = _description}

	DECLARE_FLAG('p', FLAG_P, "echo STDIN to STDOUT and append the checksum to STDOUT"),
	DECLARE_FLAG('q', FLAG_Q, "quiet mode"),
	DECLARE_FLAG('r', FLAG_R, "reverse the format of the output"),
	DECLARE_FLAG('s', FLAG_S, "print the sum of the given string")
};

static t_algorithm		parser_algorithm_get(char *command)
{
	uint8_t i;

	i = 0;
	while (i < ALGORITHM_AMOUNT)
	{
		if (ft_strequ((const char *)g_algorithms[i].name, command))
		{
			return (g_algorithms[i]);
		}
		i++;
	}
	ft_ssl_error(INVALID_COMMAND, command);
	return (g_algorithms[0]);
}

static void				parser_options(t_parser_data *parsed_data,
											char *current_arg)
{
	uint8_t i;
	uint8_t symbol_inputed;

	/**
	 * @brief skip '-' symbol.
	 */
	symbol_inputed = *(current_arg + 1);

	i = 0;
	while (i < FLAGS_AMOUNT)
	{
		if (symbol_inputed == g_flags[i].name) {
			parsed_data->options |= g_flags[i].mask;
			/**
			 * @brief check correctness of end of the argument.
			 */
			symbol_inputed = *(current_arg + 2);
			if (symbol_inputed != '\0') {
				ft_ssl_error(INVALID_OPTION, current_arg + 1);
			}
			return ;
		}
		i++;
	}
	ft_ssl_error(INVALID_OPTION, current_arg + 1);
}

static void				parser_files(t_parser_data *parsed_data,
										int argc, char **argv)
{
	int files_count;

	files_count = 0;
	while (files_count < argc)
	{
		parsed_data->files_data[files_count] = *(argv + files_count);
		files_count++;
		parsed_data->files_data[files_count] = NULL;
	}
}

static void				parser_all_args_get(t_parser_data *parsed_data,
												int argc, char **argv)
{
	int		s_count;
	int		i;

	i = -1;
	s_count = 0;
	while (++i < argc)
	{
		if (argv[i][0] == '-')
		{
			parser_options(parsed_data, *(argv + i));
			if (argv[i][1] == 's')
			{
				i++;
				if (i < argc)
					parsed_data->s_option_data[s_count] = argv[i];
				else
					ft_ssl_error(EXPECTED_ARGUMENT, NULL);
				s_count++;
				parsed_data->s_option_data[s_count] = NULL;
			}
		}
		else
			break ;
	}
	parser_files(parsed_data, argc - i, argv + i);
}

t_parser_data		parser(int argc, char **argv)
{
	t_parser_data parsed_data;

	parsed_data.options = 0;
	if (argc == 1)
		ft_ssl_error(USAGE, *(argv + 1));
	parsed_data.algorithm = parser_algorithm_get(*(argv + 1));
	parsed_data.s_option_data[0] = NULL;
	parsed_data.files_data[0] = NULL;
	if (argc > 2)
		parser_all_args_get(&parsed_data, argc - 2, argv + 2);
	return (parsed_data);
}
