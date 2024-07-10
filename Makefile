NAME = so_long

CC = cc
CFLAGS = -Wall -Wextra -Werror

MLX_DIR = src
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_INC = -Iminilibx_opengl_20191021
MLX = $(MLX_LIB) -framework OpenGL -framework AppKit

SRC = src/main.c src/game.c src/map.c src/graphics.c src/get_next_line.c src/get_next_line_utils.c
OBJ = $(SRC:.c=.o)

INCLUDES = -Iinclude $(MLX_INC)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(MLX) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
