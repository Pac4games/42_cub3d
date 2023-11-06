NAME := libft.a
CC := cc
CFLAGS := -Wall -Wextra -Werror -g
SRCS := ft_strlen.c ft_printf.c ft_putnbr_base.c\
        get_next_line.c get_next_line_utils.c\
        ft_strnstr.c ft_split.c ft_strjoin.c\
        ft_atoi.c ft_itoa.c ft_strtrim.c ft_strchr.c\
        ft_split_spaces.c ft_memset.c ft_isdigit.c\
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c\
		ft_memcpy.c ft_strdup.c

OBJS := $(SRCS:.c=.o)

all: $(NAME)

$(NAME) : $(OBJS)
	ar rc $(NAME) $(OBJS)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf libft.a

re: fclean all

.PHONY: all clean fclean re
