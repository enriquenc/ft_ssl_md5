/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaslyan <tmaslyan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 14:34:40 by tmaslyan          #+#    #+#             */
/*   Updated: 2020/04/18 22:58:42 by tmaslyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

static void	digest_to_hex_string(uint8_t *hex_str_buf, uint8_t *digest,
																int len)
{
	int		i;
	int		hex_string_size;
	char	*hex_str;

	i = 0;
	hex_string_size = 0;
	while (i < len)
	{
		hex_str = itoa_base(digest[i], 16, 'a');
		if (digest[i] < 16)
			ft_memcpy(hex_str_buf + hex_string_size++, "0", 1);
		ft_memcpy(hex_str_buf + hex_string_size, hex_str, ft_strlen(hex_str));
		hex_string_size += ft_strlen(hex_str);
		free(hex_str);
		i++;
	}
	hex_str_buf[hex_string_size] = 0;
}

static void	from_stdin_encryption(t_parser_data *parsed, uint8_t *buf,
													uint8_t *digest)
{
	read_from_descriptor(buf, 0);
	parsed->algorithm.hash_function(digest, buf);
	if (parsed->options & FLAG_P)
		ft_printf("%s", buf);
	digest_to_hex_string(buf, digest, parsed->algorithm.hash_size_bytes);
	if (!(parsed->options & (FLAG_Q | FLAG_R)))
		ft_printf("%s (stdin) = %s\n", parsed->algorithm.name, buf);
	else if (!(parsed->options & FLAG_Q))
		ft_printf("%s stdin\n", buf);
	else
		ft_printf("%s\n", buf);
}

static void	from_s_argument_encrypt(t_parser_data *parsed, uint8_t *src,
											uint8_t *buf, uint8_t *digest)
{
	parsed->algorithm.hash_function(digest, src);
	digest_to_hex_string(buf, digest, parsed->algorithm.hash_size_bytes);
	if (!(parsed->options & (FLAG_Q | FLAG_R)))
		ft_printf("%s (\"%s\") = %s\n", parsed->algorithm.name, src, buf);
	else if (!(parsed->options & FLAG_Q))
		ft_printf("%s \"%s\"\n", buf, src);
	else
		ft_printf("%s\n", buf);
}

static void	from_file_encryption(t_parser_data *parsed, char *file,
											uint8_t *buf, uint8_t *digest)
{
	parsed->algorithm.hash_function(digest, buf);
	digest_to_hex_string(buf, digest, parsed->algorithm.hash_size_bytes);
	if (!(parsed->options & (FLAG_Q | FLAG_R)))
		ft_printf("%s (%s) = %s\n", parsed->algorithm.name, file, buf);
	else if (!(parsed->options & FLAG_Q))
		ft_printf("%s %s\n", buf, file);
	else
		ft_printf("%s\n", buf);
}

void		connector(t_parser_data *parsed)
{
	char	**str_arr;
	char	**f_arr;
	uint8_t	buf[MAX_BUFFER_SIZE];
	uint8_t	digest[256];
	int		i;

	i = 0;
	str_arr = parsed->s_option_data;
	f_arr = parsed->files_data;
	if ((str_arr[0] == NULL && f_arr[0] == NULL) || parsed->options & FLAG_P)
		from_stdin_encryption(parsed, buf, digest);
	while (str_arr[i])
		from_s_argument_encrypt(parsed, (uint8_t *)str_arr[i++], buf, digest);
	i = 0;
	while (f_arr[i])
	{
		if (get_file_content(buf, f_arr[i]))
			from_file_encryption(parsed, f_arr[i], buf, digest);
		i++;
	}
}
