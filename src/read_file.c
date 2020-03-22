/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaslyan <tmaslyan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 00:55:57 by tmaslyan          #+#    #+#             */
/*   Updated: 2020/03/22 13:37:42 by tmaslyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <fcntl.h>

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
	if (line)
	{
		ft_memcpy(dest + size, line, strlen(line));
		size += strlen(line);
	}
	*(dest + size) = 0;
	free(line);
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
