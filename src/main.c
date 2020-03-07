#include <connector.h>

t_algorithms g_algorithms[MAX] = {
	{.name = "md5", .alg = MD5},
	{.name = "sha256", .alg = SHA256}
};

t_hash_algorithm parser_algorithm_get(char *command) {
	uint8_t i;

	i = 0;
	while (i < MAX) {
		if (ft_strequ((const char *)g_algorithms[i].name, command)) {
			return g_algorithms[i].alg;
		}
		i++;
	}
	ft_ssl_error(INVALID_COMMAND, command);
	return MAX;
}

void parser_options(t_parser_data *parsed_data, char *current_arg)
{
	switch (current_arg[1])
	{
		case 'p':
			parsed_data->options |= FLAG_P;
			break;
		case 'q':
			parsed_data->options |= FLAG_Q;
			break;
		case 'r':
			parsed_data->options |= FLAG_R;
			break;
		case 's':
			parsed_data->options |= FLAG_S;
			break;
		default:
			ft_ssl_error(INVALID_OPTION, current_arg + 1);
			break;
	}
	if (current_arg[2] != '\0')
		ft_ssl_error(INVALID_OPTION, current_arg + 1);
}

void parser_files(t_parser_data *parsed_data, int argc, char **argv)
{
	int files_count;

	files_count = 0;
	while (files_count < argc) {
		parsed_data->files_data[files_count] = *(argv + files_count);
		files_count++;
		parsed_data->files_data[files_count] = NULL;
	}
}

void parser_all_args_get(t_parser_data *parsed_data, int argc, char **argv)
{
	char *current_arg;
	int s_count;
	int i;

	i = 0;
	s_count = 0;
	while (i < argc) {
		current_arg = *(argv + i);
		if (current_arg[0] == '-') {
			parser_options(parsed_data, current_arg);
			if (current_arg[1] == 's') {
				i++;
				if (i < argc)
					parsed_data->s_option_data[s_count] = *(argv + i);
				else
					ft_ssl_error(EXPECTED_ARGUMENT, NULL);
				s_count++;
				parsed_data->s_option_data[s_count] = NULL;
			}
		} else
			break;
		i++;
	}
	parser_files(parsed_data, argc - i, argv + i);
}

t_parser_data parser(int argc, char **argv)
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

	return parsed_data;
}

int main(int argc, char **argv) {
	t_parser_data parsed_data;

	parsed_data = parser(argc, argv);
	connector(&parsed_data);
	return 0;
}
