/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaslyan <tmaslyan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 14:34:40 by tmaslyan          #+#    #+#             */
/*   Updated: 2020/03/07 16:05:14 by tmaslyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <connector.h>
#include <fcntl.h>

t_hash_functions g_all[MAX] = {
	{.func = md5},
	{.func = sha256}
};

extern t_algorithms g_algorithms[MAX];

void		read_from_descriptor(uint8_t *dest, int fd)
{
	int		size;
	char	*line;

	size = 0;
	while (get_next_line(fd, &line) && line)
	{
		ft_memcpy(dest + size, line, strlen(line));
		size += strlen(line);
		ft_memcpy(dest + size, "\n", 1);
		size++;
	}
}

uint8_t		get_file_content(uint8_t *dest, char *file_name)
{
	int fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("ft_ssl: \"%s\": No such file or directory\n", file_name);
		return (0);
	}
	read_from_descriptor(dest, fd);
	close(fd);
	return (1);
}

const char	*get_algorithm_str(t_hash_algorithm alg)
{
	int		i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < MAX)
	{
		if (g_algorithms[i].alg == alg)
		{
			while (j < ft_strlen(g_algorithms[i].name))
			{
				g_algorithms[i].name[j] = ft_toupper(g_algorithms[i].name[j]);
				j++;
			}
			return (g_algorithms[i].name);
		}
	}
	return ("(NULL)");
}

void		connector(t_parser_data *parsed_data)
{
	t_ssl message_data;
	char **string_array;
	char **files_array;
	int i;

	i = 0;
	string_array = parsed_data->s_option_data;
	files_array = parsed_data->files_data;

	if ((string_array[0] == NULL && files_array[0] == NULL) ||
									parsed_data->options & FLAG_P)
	{
		read_from_descriptor(message_data.message, 0);
		if (!(parsed_data->options & FLAG_Q) && parsed_data->options & FLAG_P)
			ft_printf("%s", message_data.message);
		g_all[parsed_data->algorithm].func(&message_data);
		ft_putchar('\n');
	}

	while (string_array[i])
	{
		if (!(parsed_data->options & FLAG_Q) && !(parsed_data->options & FLAG_R))
			ft_printf("%s (\"%s\") = ", get_algorithm_str(parsed_data->algorithm), string_array[i]);
		ft_memcpy(message_data.message, string_array[i], strlen(string_array[i]) + 1);
		g_all[parsed_data->algorithm].func(&message_data);
		if (!(parsed_data->options & FLAG_Q) && parsed_data->options & FLAG_R)
			ft_printf(" \"%s\"", string_array[i]);
		i++;
	}
	if (i)
		ft_putchar('\n');
	i = 0;
	while (files_array[i])
	{
		if (get_file_content(message_data.message, files_array[i]))
		{
			if (!(parsed_data->options & FLAG_Q) && !(parsed_data->options & FLAG_R))
				ft_printf("%s (%s) = \n", get_algorithm_str(parsed_data->algorithm), files_array[i]);
			g_all[parsed_data->algorithm].func(&message_data);
			if (!(parsed_data->options & FLAG_Q) && parsed_data->options & FLAG_R)
				ft_printf(" %s\n", files_array[i]);
		}
		i++;
	}
	if (parsed_data->options & FLAG_Q)
		ft_putchar('\n');
}
