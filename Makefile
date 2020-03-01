NAME = ft_ssl

SRCNAME	= md5.c connector.c main.c

SRC = $(addprefix src/, $(SRCNAME))
OBJECT = $(SRC:.c=.o)
FLAGS  = -Wall -Wextra -Werror
HDIR = include
LIBHDIR = libft/include
LIBFT = libft/libft.a

all: lib $(NAME)

$(NAME):$(OBJECT) $(LIBFT) $(HDIR) $(LIBHDIR)
	gcc $(OBJECT) $(LIBFT) $(FLAGS) -o $(NAME)

lib:
	make -C libft

%.o: %.c
	gcc $(FLAGS) -o $@ -c $< -I $(HDIR) -I $(LIBHDIR)

clean:
	rm -f $(OBJECT)
	make clean -C libft

fclean: clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean all
