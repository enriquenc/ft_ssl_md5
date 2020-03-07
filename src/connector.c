/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaslyan <tmaslyan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 14:34:40 by tmaslyan          #+#    #+#             */
/*   Updated: 2020/03/08 00:07:29 by tmaslyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <connector.h>
#include <fcntl.h>

void		read_from_descriptor(uint8_t *dest, int fd)
{
	int		size;
	char	*line;

	size = 0;
	int er;
	while ((er = get_next_line(fd, &line)) && line)
	{
		ft_memcpy(dest + size, line, strlen(line));
		size += strlen(line);
		ft_memcpy(dest + size, "\n", 1);
		size++;
	}
	if (line) {
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

uint8_t *digest_to_hex_string(uint8_t *hex_string_buf, uint8_t *digest, int len) {
	int i = 0;
	int hex_string_size;
	char *hex_str;

	hex_string_size = 0;
	while (i < len) {
		hex_str = itoa_base(digest[i], 16, 'a');
		if (digest[i] < 16)
			ft_memcpy(hex_string_buf + hex_string_size++, "0", 1);
		ft_memcpy(hex_string_buf + hex_string_size, hex_str, ft_strlen(hex_str));
		hex_string_size += ft_strlen(hex_str);
		free(hex_str);
		i++;
	}
	hex_string_buf[hex_string_size] = 0;
	return hex_string_buf;
}

void		from_stdin_encryption(t_parser_data *parsed, uint8_t *buf, uint8_t *digest)
{
	read_from_descriptor(buf, 0);
	parsed->algorithm.func(digest, buf);
	if (parsed->options & FLAG_P)
		ft_printf("%s", buf);
	digest_to_hex_string(buf, digest, parsed->algorithm.digest_len_bytes);
	ft_printf("%s\n", buf);
}

void		from_s_argument_encryption(t_parser_data *parsed, uint8_t *src, uint8_t *buf, uint8_t *digest)
{
	parsed->algorithm.func(digest, src);
	digest_to_hex_string(buf, digest, parsed->algorithm.digest_len_bytes);
	if (!(parsed->options & FLAG_Q) && !(parsed->options & FLAG_R))
		ft_printf("%s (\"%s\") = %s\n", parsed->algorithm.name, src, buf);
	else if (!(parsed->options & FLAG_Q) && parsed->options & FLAG_R)
		ft_printf("%s \"%s\"\n", buf, src);
	else
		ft_printf("%s\n", buf);
}

void		from_file_encryption(t_parser_data *parsed, char *file, uint8_t *buf, uint8_t *digest)
{
	parsed->algorithm.func(digest, buf);
	digest_to_hex_string(buf, digest, parsed->algorithm.digest_len_bytes);
	if (!(parsed->options & FLAG_Q) && !(parsed->options & FLAG_R))
		ft_printf("%s (%s) = %s\n", parsed->algorithm.name, file, buf);
	else if (!(parsed->options & FLAG_Q) && parsed->options & FLAG_R)
		ft_printf("%s %s\n", buf, file);
	else
		ft_printf("%s\n", buf);
}

void		connector(t_parser_data *parsed)
{
	char **str_arr;
	char **f_arr;
	uint8_t buf[MAX_BUFFER_SIZE];
	uint8_t digest[128];
	int i;

	i = 0;
	str_arr = parsed->s_option_data;
	f_arr = parsed->files_data;

	if ((str_arr[0] == NULL && f_arr[0] == NULL) || parsed->options & FLAG_P)
		from_stdin_encryption(parsed, buf, digest);

	while (str_arr[i])
		from_s_argument_encryption(parsed, (uint8_t *)str_arr[i++], buf, digest);

	i = 0;
	while (f_arr[i])
	{
		if (get_file_content(buf, f_arr[i]))
			from_file_encryption(parsed, f_arr[i], buf, digest);
		i++;
	}
}
