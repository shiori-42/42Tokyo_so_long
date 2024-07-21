NAME = so_long

CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX_DIR = mlx
LIBFT_DIR = libft
INCLUDES = -Iincludes -I$(MLX_DIR) -I$(LIBFT_DIR)/includes

LIBFT = $(LIBFT_DIR)/libft.a
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX = $(MLX_LIB) -L$(MLX_DIR) -L/usr/lib/X11 -lXext -lX11 

SRCS_DIR = src
SRC_FILES = check_path.c main.c utils.c game.c map.c path_utils.c map_validation.c map_creation.c
SRCS = $(addprefix $(SRCS_DIR)/, $(SRC_FILES))
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(SRCS_DIR)/%.o: $(SRCS_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(LIBFT) $(MLX_LIB) $(OBJS)
	$(CC) $(OBJS) $(MLX) $(LIBFT) -o $(NAME)
	@echo "Executable $(NAME) created."

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(MLX_DIR) || true
	rm -f $(OBJS)
	@echo "Object files cleaned."

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	-$(MAKE) fclean -C $(MLX_DIR) || true
	rm -f $(NAME)
	@echo "Executable $(NAME) removed."

re: fclean all

.PHONY: all clean fclean re
