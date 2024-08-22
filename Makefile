NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror

MLX_DIR = mlx
LIBFT_DIR = libft
SRCS_DIR = src
INCLUDES = -Iincludes -I$(MLX_DIR) -I$(LIBFT_DIR)/includes

SRC_FILES = check_path.c \
            main.c \
            game.c \
            map.c \
            map_validation.c \
            path.c \
            free_resources.c \
			
SRCS = $(addprefix $(SRCS_DIR)/, $(SRC_FILES))
OBJS = $(SRCS:.c=.o)

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Darwin)
    CFLAGS += -I/opt/homebrew/Cellar/libx11/1.8.10/include -I/opt/homebrew/Cellar/libxext/1.3.6/include -DGL_SILENCE_DEPRECATION
    LIBS = -L/opt/homebrew/Cellar/libx11/1.8.10/lib -L/opt/homebrew/Cellar/libxext/1.3.6/lib -lXext -lX11 -framework OpenGL -framework AppKit
else
    CFLAGS += -I/usr/include
    LIBS = -L/usr/lib/X11 -lXext -lX11 -lm
endif

LIBFT = $(LIBFT_DIR)/libft.a
MLX_LIB = $(MLX_DIR)/libmlx.a

GIT_MLX = git clone https://github.com/42Paris/minilibx-linux.git $(MLX_DIR)

all: $(NAME)

$(MLX_DIR):
	if [ ! -d "$(MLX_DIR)" ]; then \
	    $(GIT_MLX); \
	fi

$(SRCS_DIR)/%.o: $(SRCS_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(MLX_DIR) $(LIBFT) $(MLX_LIB) $(OBJS)
	$(CC) $(OBJS) $(MLX_LIB) $(LIBFT) $(LIBS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(MLX_DIR)
	rm -f $(OBJS)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(MLX_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re