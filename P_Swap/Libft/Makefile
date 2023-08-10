NAME = libft.a

GCC = gcc

SRC = ft_isalpha.c \
      ft_isdigit.c \
      ft_isalnum.c \
      ft_isascii.c \
      ft_isprint.c \
      ft_strlen.c \
      ft_memset.c \
      ft_bzero.c \
      ft_memcpy.c \
      ft_memmove.c \
      ft_strlcpy.c \
      ft_strlcat.c \
      ft_toupper.c \
      ft_tolower.c \
      ft_strchr.c \
      ft_strrchr.c \
      ft_strncmp.c \
      ft_memchr.c \
      ft_memcmp.c \
      ft_strnstr.c \
      ft_atoi.c \
      ft_calloc.c \
      ft_strdup.c \
      ft_substr.c \
      ft_strjoin.c \
      ft_strtrim.c \
      ft_split.c \
      ft_itoa.c \
      ft_strmapi.c \
      ft_striteri.c \
      ft_putchar_fd.c \
      ft_putstr_fd.c \
      ft_putendl_fd.c \
      ft_putnbr_fd.c \
      get_next_line.c \

FLAGS = -Wall -Wextra -Werror

OBJ = ${SRC:.c=.o}

.c.o:
	${GCC} ${FLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${OBJ}
	make -C Printf/
	cp Printf/libftprintf.a .
	mv libftprintf.a ${NAME}
	ar rc ${NAME} ${OBJ}

all: ${NAME}

bonus: all

clean:
	make clean -C Printf/
	rm -f ${OBJ}

fclean: clean
	make fclean -C Printf/
	rm -f ${NAME}

re: fclean all

.PHONY:	all bonus clean fclean re
