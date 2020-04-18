/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_error_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaslyan <tmaslyan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 14:35:24 by tmaslyan          #+#    #+#             */
/*   Updated: 2020/04/18 18:25:33 by tmaslyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

static void	print_valid_commands(void)
{
	int i;

	i = 0;
	ft_printf("Message Digest commands:\n");
	while (i < ALGORITHM_AMOUNT) {
		ft_printf("%s\n", g_algorithms[i].name);
		i++;
	}
}

static void print_valid_options(void)
{
	int i;

	i = 0;
	ft_printf("Flags:\n");
	while (i < FLAGS_AMOUNT) {
		ft_printf("-%c\t%s\n", g_flags[i].name, g_flags[i].description);
		i++;
	}
}

void	ft_ssl_error(t_error code, void *arg)
{
	if (code == USAGE)
		ft_printf("usage: ft_ssl command [command opts] [command args]\n");
	else if (code == INVALID_COMMAND)
	{
		ft_printf("ft_ssl: Error: '%s' is an invalid command.\n\n",
														(char *)arg);
		print_valid_commands();
	}
	else if (code == INVALID_OPTION)
	{
		ft_printf("ft_ssl: Unknown option '%s'\n\n", (char *)arg);
		print_valid_options();
	}
	else if (code == EXPECTED_ARGUMENT)
		ft_printf("ft_ssl: Expected argument after -s.\n");
	exit(0);
}
