NAME = philo
CC = gcc -Wextra -Wall -Werror
SRCS = *.c
RM = rm - f

all : $(NAME)

$(NAME) :
	@$(CC) -pthread $(SRCS) -o $(NAME)

clean:
	@$(MAKE) clean -C

fclean: clean
	@$(MAKE) fclean -C
	@$(RM) $(NAME)

re: fclean all
