NAME = philo
LIB = philo.h
C_SOURCES = philo.c philo_utils.c actions.c actions_utils.c
CC = @cc
CFLAGS = -Wall -Wextra -Werror -g -lpthread

all:	$(NAME)
$(NAME):	$(C_SOURCES)
			$(CC) $(CFLAGS) $(^) -o $(@)
#-fsanitize=thread

clean:
		@rm -f *.o

fclean: clean
		@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re