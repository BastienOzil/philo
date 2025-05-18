.SILENT:

YELLOW = \033[1;33m
GREEN = \033[1;32m
RESET = \033[0m

NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRC_DIR = srcs

OBJS_DIR = objs

SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/init.c $(SRC_DIR)/simulation.c $(SRC_DIR)/actions.c\
$(SRC_DIR)/parse.c $(SRC_DIR)/philo_life.c $(SRC_DIR)/forks.c $(SRC_DIR)/utils.c

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)Yeay, it compile!"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR) --no-print-directory

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

%.o: %.c
	@$(CC) $(CFLAGS) -I$(PRINTF_DIR) -I$(LIBFT_DIR) -g3 -c $< -o $@

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
