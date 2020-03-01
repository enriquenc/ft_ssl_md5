#include <connector.h>




int main(int argc, char **argv) {
	(void)argc;
	t_ssl alg;
	ft_strcpy((char *)alg.message, *(argv + 1));
	alg.algorithm = 0;
	connector(&alg);

	return 0;
}
