NAME = so_long
CC = cc

# Common flags and directories
MLX_DIR = mlx
LIBFT_DIR = libft
SRCS_DIR = src
INCLUDES = -Iincludes -I$(MLX_DIR) -I$(LIBFT_DIR)/includes

# Source files
SRC_FILES = check_path.c \
            game.c \
            main.c \
            map.c \
            map_validation.c \
            path.c \
            utils.c \
            handler.c
SRCS = $(addprefix $(SRCS_DIR)/, $(SRC_FILES))
OBJS = $(SRCS:.c=.o)

# Detect the OS
UNAME_S := $(shell uname -s)

# Common Flags
CFLAGS = -Werror -Wall -Wextra

# OS-specific settings
ifeq ($(UNAME_S), Darwin)
    CFLAGS += -I/opt/homebrew/Cellar/libx11/1.8.10/include -I/opt/homebrew/Cellar/libxext/1.3.6/include -DGL_SILENCE_DEPRECATION
    LIBS = -L/opt/homebrew/Cellar/libx11/1.8.10/lib -L/opt/homebrew/Cellar/libxext/1.3.6/lib -lXext -lX11 -framework OpenGL -framework AppKit
else
    CFLAGS += -I/usr/include
    LIBS = -L/usr/lib/X11 -lXext -lX11 -lm
endif


# Library targets
LIBFT = $(LIBFT_DIR)/libft.a
MLX_LIB = $(MLX_DIR)/libmlx.a

# Git clone command for MLX
GIT_MLX = git clone https://github.com/42Paris/minilibx-linux.git $(MLX_DIR)

# Default target
all: $(NAME)

# Ensure MLX directory exists
$(MLX_DIR):
	$(GIT_MLX)

# Object file compilation
$(SRCS_DIR)/%.o: $(SRCS_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Executable linking
$(NAME): $(MLX_DIR) $(LIBFT) $(MLX_LIB) $(OBJS)
	$(CC) $(OBJS) $(MLX_LIB) $(LIBFT) $(LIBS) -o $(NAME)

# Build libft
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Build mlx
$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

# Clean object files
clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(MLX_DIR)
	rm -f $(OBJS)

# Full clean
fclean: clean
	rm -rf $(LIBFT)
	rm -rf $(MLX_LIB)
	rm -f $(NAME)

# Rebuild
re: fclean all

.PHONY: all clean fclean re