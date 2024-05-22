RED=\033[0;31m
GREEN=\033[0;32m
RESET=\033[0m

NAME = philo

SRCS = error_handling.c initialize.c main.c mutex_handling.c parsing.c supervisor.c utils.c dinner.c simulation.c

OBJS = ${SRCS:.c=.o}

CC = cc

CFLAGS = -Wall -Wextra -Werror

LIB = philo.h

all: ${NAME}

${NAME}: $(OBJS)
				$(CC) $(FLAGS) $(OBJS) -o $(NAME)
				@echo "$(NAME): $(GREEN)$(OBJS) was created $(RESET)"

clean:
				rm -f $(OBJS)
				@echo "$(NAME): $(RED)$(OBJS) was deleted $(RESET)"

fclean: clean
				rm -f $(NAME)
				@echo "$(NAME): $(RED)$(NAME) was deleted $(RESET)"

re: fclean all

.PHONY: all clean fclean re