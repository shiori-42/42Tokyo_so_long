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

# Flags and libraries for macOS
ifeq ($(UNAME_S), Darwin)
    CFLAGS += -I/opt/homebrew/Cellar/libx11/1.8.10/include -I/opt/homebrew/Cellar/libxext/1.3.6/include -DGL_SILENCE_DEPRECATION
    LIBS = -L/opt/homebrew/Cellar/libx11/1.8.10/lib -L/opt/homebrew/Cellar/libxext/1.3.6/lib -lXext -lX11 -framework OpenGL -framework AppKit
    MLX = $(MLX_LIB) -L$(MLX_DIR) $(LIBS)
# Flags and libraries for Linux
else
    CFLAGS += -I/usr/include
    LIBS = -L/usr/lib/X11 -lXext -lX11
    MLX = $(MLX_LIB) -L$(MLX_DIR) $(LIBS)
endif

# Library targets
LIBFT = $(LIBFT_DIR)/libft.a
MLX_LIB = $(MLX_DIR)/libmlx.a

# Default target
all: $(NAME)

# Object file compilation
$(SRCS_DIR)/%.o: $(SRCS_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Executable linking
$(NAME): $(LIBFT) $(MLX_LIB) $(OBJS)
	$(CC) $(OBJS) $(MLX) $(LIBFT) -o $(NAME)

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
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(MLX_DIR)
	rm -f $(NAME)

# Rebuild
re: fclean all

.PHONY: all clean fclean re