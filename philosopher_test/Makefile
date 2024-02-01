.PHONY: all clean fclean re
NAME	= philo

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g -pthread
RM		= rm -rf

SRCS	= $(wildcard *.c)
OBJS	= $(SRCS:.c=.o)

$$(NAME): $(OBJS) philo.h
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all