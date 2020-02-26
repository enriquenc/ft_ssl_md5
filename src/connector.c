#include <connector.h>

t_hash_functions all[MAX] = {
	{.func = md5}
};


void connector(t_ssl *message_data) {
	all[MD5].func(message_data);
}