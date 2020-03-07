#include <connector.h>

extern t_algorithms g_algorithms[MAX];

void print_valid_commands()
{
	int i;

	i = 0;
	ft_printf("Message Digest commands:\n");
	while (i < MAX)
		ft_printf("%s\n", g_algorithms[i++].name);
}

void ft_ssl_error(t_error code, void *arg) {
	switch (code)
	{
		case USAGE:
			ft_printf("usage: ft_ssl command [command opts] [command args]\n");
			break;
		case INVALID_COMMAND:
			ft_printf("ft_ssl: Error: '%s' is an invalid command.\n\n", (char *)arg);
			print_valid_commands();
			break;
		case INVALID_OPTION:
			ft_printf("ft_ssl: Unknown option '%s'\n", (char * )arg);
			break;
		case EXPECTED_ARGUMENT:
			ft_printf("ft_ssl: Expected argument after -s.\n");
			break;
		default:
			break;
	}
	exit(0);
}