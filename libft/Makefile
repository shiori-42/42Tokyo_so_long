NAME = libft.a
CC = cc
INCLUDES = includes
CFLAGS = -Wall -Wextra -Werror $(addprefix -I,$(INCLUDES))

SRCS = ft_isdigit.c ft_memset.c ft_strdup.c ft_strncmp.c \
       ft_atoi.c ft_isprint.c ft_putchar_fd.c ft_striteri.c ft_strnstr.c \
       ft_bzero.c ft_itoa.c ft_putendl_fd.c ft_strjoin.c ft_strrchr.c \
       ft_calloc.c ft_memchr.c ft_putnbr_fd.c ft_strlcat.c ft_strtrim.c \
       ft_isalnum.c ft_memcmp.c ft_putstr_fd.c ft_strlcpy.c ft_substr.c \
       ft_isalpha.c ft_memcpy.c ft_split.c ft_strlen.c ft_tolower.c \
       ft_isascii.c ft_memmove.c ft_strchr.c ft_strmapi.c ft_toupper.c

GNL_SRCS = $(addprefix gnl/, get_next_line.c get_next_line_utils.c)

FT_PRINTF_SRCS = $(addprefix printf/, ft_itoa_base.c ft_printf.c handle_d_or_i.c handle_p.c \
                 handle_s.c handle_upperhex.c ft_itoa_base_ptr.c \
                 handle_c.c handle_lowhex.c handle_percent_symbol.c handle_u.c)

SRCS_BONUS = ft_lstnew_bonus.c ft_lstiter_bonus.c ft_lstclear_bonus.c \
             ft_lstdelone_bonus.c ft_lstadd_back_bonus.c ft_lstlast_bonus.c \
             ft_lstsize_bonus.c ft_lstadd_front_bonus.c ft_lstmap_bonus.c

OBJS = $(SRCS:.c=.o) $(GNL_SRCS:.c=.o) $(FT_PRINTF_SRCS:.c=.o)

ifdef WITH_BONUS
OBJS += $(SRCS_BONUS:.c=.o)
endif

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

bonus:
	make WITH_BONUS=1 all

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(OBJS_BONUS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus