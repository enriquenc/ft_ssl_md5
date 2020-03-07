/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_error_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaslyan <tmaslyan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 14:35:24 by tmaslyan          #+#    #+#             */
/*   Updated: 2020/03/07 15:25:54 by tmaslyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <connector.h>

extern t_algorithms g_algorithms[MAX];

void	print_valid_commands(void)
{
	int i;

	i = 0;
	ft_printf("Message Digest commands:\n");
	while (i < MAX)
		ft_printf("%s\n", g_algorithms[i++].name);
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
		ft_printf("ft_ssl: Unknown option '%s'\n", (char *)arg);
	else if (code == EXPECTED_ARGUMENT)
		ft_printf("ft_ssl: Expected argument after -s.\n");
	exit(0);
}
