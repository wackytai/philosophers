NAME = philo
LIB = philo.h
C_SOURCES = philo.c philo_utils.c
B_SOURCES = 
CC = @cc
CFLAGS = -Wall -Wextra -Werror -g

all:	$(NAME)
$(NAME):	$(C_SOURCES)
			@$(CC) $(CFLAGS) $(^) -o $(NAME) -fsanitize=address

bonus: $(B_SOURCES)
			@$(CC) $(CFLAGS) $(^) -o $(NAME) -fsanitize=address

clean:
		@rm -f *.o

fclean: clean
		@rm -f $(NAME)

re: fclean all

reb: fclean bonus

.PHONY: all bonus clean fclean re reb