#include <md5.h>


void md5_message_padding(t_ssl *message_data) {

	while (++message_data->message_len % DIV_BYTES != NEEDED_MODULO_BYTES);

	ft_printf("%d\n", message_data->message_len);
}

size_t md5(t_ssl *message_data) {
	//char buf[MAX_BUFFER_SIZE];

	// size_t arg_len = 0;
	// if (*(argv + 1))
	// 	arg_len = ft_strlen(*(argv + 1));

	//int len = ft_atoi((const char *)message_data->message);
	message_data->message_len = ft_strlen((const char *)message_data->message) + 440 / 8;
	md5_message_padding(message_data);
	ft_printf("%s\n", (const char *)message_data->message);
	//(len);
	return 0;
}