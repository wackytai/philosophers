NAME = philo_bonus
LIB = philo_bonus.h
C_SOURCES = philo_bonus.c philo_bonus_utils.c philo_bonus_finish.c philo_bonus_actions.c
CC = @cc
CFLAGS = -Wall -Wextra -Werror -g -lpthread -lrt

all:	$(NAME)
$(NAME):	$(C_SOURCES)
			$(CC) $(CFLAGS) $(^) -o $(@) -fsanitize=address

clean:
		@rm -f *.o

fclean: clean
		@rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re