NAME = so_long

CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX_DIR = mlx
LIBFT_DIR=libft
INCLUDES = -Iincludes -I$(MLX_DIR) -I.$(LIBFT_DIR)

LIBFT = $(LIBFT_DIR)/libft.a

MLX_LIB = $(MLX_DIR)/libmlx.a
MLX = $(MLX_LIB) -L$(MLX_DIR) -L/usr/lib/X11 -lXext -lX11 

SRCS_DIR = src/
SRC_FILES = main.c game.c map.c
SRCS = $(addprefix $(SRCS_DIR)/, $(SRC_FILES))
OBJS = $(SRCS:.c=.o)

all: $(MLX_LIB) $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(MLX) $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MLX_LIB):
	make -C $(MLX_DIR)

clean:
	make clean -C $(LIBFT_DIR)
	make clean -C $(MLX_DIR)
	rm -f $(OBJS)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	make fclean -C $(MLX_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

