/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaslyan <tmaslyan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 14:52:47 by tmaslyan          #+#    #+#             */
/*   Updated: 2020/03/07 22:46:33 by tmaslyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <connector.h>

t_algorithm g_algorithms[MAX] = {
	{.name = "md5", .num = MD5, .func = md5, .digest_len_bytes = 16},
	{.name = "sha256", .num = SHA256, .func = sha256, .digest_len_bytes = 32},
};

t_algorithm			parser_algorithm_get(char *command)
{
	uint8_t i;

	i = 0;
	while (i < MAX)
	{
		if (ft_strequ((const char *)g_algorithms[i].name, command))
		{
			return (g_algorithms[i]);
		}
		i++;
	}
	ft_ssl_error(INVALID_COMMAND, command);
	return g_algorithms[0];
}

void				parser_options(t_parser_data *parsed_data,
											char *current_arg)
{
	if (current_arg[1] == 'p')
		parsed_data->options |= FLAG_P;
	else if (current_arg[1] == 'q')
		parsed_data->options |= FLAG_Q;
	else if (current_arg[1] == 'r')
		parsed_data->options |= FLAG_R;
	else if (current_arg[1] == 's')
		parsed_data->options |= FLAG_S;
	else
		ft_ssl_error(INVALID_OPTION, current_arg + 1);
	if (current_arg[2] != '\0')
		ft_ssl_error(INVALID_OPTION, current_arg + 1);
}

void				parser_files(t_parser_data *parsed_data,
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

void				parser_all_args_get(t_parser_data *parsed_data,
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
