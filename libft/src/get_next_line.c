/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaslyan <tmaslyan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 16:16:18 by tmaslyan          #+#    #+#             */
/*   Updated: 2020/03/07 21:24:36 by tmaslyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static t_bufer	*get_list(t_bufer **list, int fd)
{
	if (!(*list))
	{
		if (!((*list) = (t_bufer *)malloc(sizeof(t_bufer))))
			return (NULL);
		(*list)->fd = fd;
		(*list)->buf = NULL;
		(*list)->next = NULL;
	}
	while ((*list)->next)
	{
		if ((*list)->fd == fd)
			break ;
		(*list) = (*list)->next;
	}
	if ((*list)->fd != fd)
	{
		if (!((*list)->next = (t_bufer *)malloc(sizeof(t_bufer))))
			return (NULL);
		(*list) = (*list)->next;
		(*list)->fd = fd;
		(*list)->buf = NULL;
		(*list)->next = NULL;
	}
	return (*list);
}

static int		add_to_line(t_bufer **list, char **res, char *buf)
{
	char *temp;
	char *pointer;

	if (buf == NULL)
		return (0);
	if ((temp = ft_strchr(buf, '\n')) == NULL)
	{
		(*res) = ft_strjoin(*res, buf);
		free((*list)->buf);
		(*list)->buf = NULL;
	}
	else
	{
		pointer = ft_strsub(buf, 0, temp - buf);
		(*res) = ft_strjoin(*res, pointer);
		free(pointer);
		pointer = (*list)->buf;
		if (*(++temp) == '\0')
			(*list)->buf = NULL;
		else
			(*list)->buf = ft_strdup(temp);
		free(pointer);
		return (1);
	}
	return (0);
}

static int		valid_check(t_bufer **s_list, t_bufer **list,
	char **line, int fd)
{
	t_bufer	*temp;
	char	buf[1];

	temp = NULL;
	if (*s_list)
		temp = *s_list;
	if (fd < 0 || !(*list = get_list(s_list, fd))
		|| read(fd, buf, 0) < 0 || line == NULL)
		return (-1);
	if (temp)
		*s_list = temp;
	return (0);
}

static int		check_buf(t_bufer **list, char **line, char *buf, int fd)
{
	int read_bytes;

	while ((read_bytes = read(fd, buf, BUFF_SIZE)))
	{
		if (read_bytes < 0)
		{
			free(buf);
			return (-1);
		}
		buf[read_bytes] = '\0';
		if (add_to_line(list, line, buf))
			break ;
	}
	if (!read_bytes || !(*line))
		return (0);
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	char			*buf;
	static	t_bufer	*s_list = NULL;
	t_bufer			*list;
	int				check;

	if (valid_check(&s_list, &list, line, fd) == -1 ||
	!(buf = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1))))
		return (-1);
	*line = NULL;
	if (add_to_line(&list, line, list->buf))
	{
		free(buf);
		return (1);
	}
	check = check_buf(&list, line, buf, fd);
	free(buf);
	return (check);
}
