NAME = so_long

CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX_DIR = mlx
INCLUDES = -Iincludes -I$(MLX_DIR)

MLX_LIB = $(MLX_DIR)/libmlx.a
MLX = $(MLX_LIB) -L$(MLX_DIR) -L/usr/lib/X11 -lXext -lX11 

SRCS_DIR = src
SRC_FILES = main.c game.c map.c get_next_line.c get_next_line_utils.c
SRCS = $(addprefix $(SRCS_DIR)/, $(SRC_FILES))
OBJS = $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

all: $(MLX_LIB) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(MLX) -o $(NAME)

$(MLX_LIB):
	make -C $(MLX_DIR)

clean:
	rm -f $(OBJS)
	make -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(MLX_DIR) clean

re: fclean all

.PHONY: all clean fclean re
