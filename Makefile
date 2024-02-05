.PHONY: all clean fclean re
NAME			= philo

CC				= gcc
CFLAGS			= -g -Wall -Wextra -Werror -pthread
RM				= rm -rf

INCLUDES		= ./includes
SRCS_DIR		= ./src
UTILS_DIR		= ./utils
OBJS_DIR		= ./obj

SRC_FILES 	= $(wildcard $(SRCS_DIR)/*.c)
UTILS_FILES = $(wildcard $(UTILS_DIR)/*.c)

SRC_OBJS 	= $(SRC_FILES:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)
UTILS_OBJS 	= $(UTILS_FILES:$(UTILS_DIR)/%.c=$(OBJS_DIR)/%.o)

OBJS = $(SRC_OBJS) $(UTILS_OBJS)


$(NAME): $(OBJS) $(INCLUDES)/philo.h
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@

$(OBJS_DIR)/%.o: $(UTILS_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all