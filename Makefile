NAME = so_long

CC = gcc
# CFLAGS = -Wall -Wextra -Werror -DGL_SILENCE_DEPRECATION -Iinclude
CFLAGS = -Wall -Wextra -Werror -DGL_SILENCE_DEPRECATION -Iinclude -Wno-unused-but-set-variable

MLX = -L. -lmlx -framework OpenGL -framework AppKit

SRC = src/main.c src/game.c src/map.c src/graphics.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(MLX)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
