/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaslyan <tmaslyan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 14:34:27 by tmaslyan          #+#    #+#             */
/*   Updated: 2020/03/07 14:53:59 by tmaslyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <connector.h>

int	main(int argc, char **argv)
{
	t_parser_data parsed_data;

	parsed_data = parser(argc, argv);
	connector(&parsed_data);
	return (0);
}
