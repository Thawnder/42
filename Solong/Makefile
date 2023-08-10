MAKEFLAGS += --silent

LIB_NAME = libft.a
LIBX_NAME = libmlx.a
PROG_NAME = so_long

GCC = cc
FLAGS = -Wall -Wextra -Werror -g

PROG_SRC = 	so_long.c \
	   	checks.c \
		utils.c \
		hooks.c	\
		sprites.c \
		anim_utils.c \
		enemies.c

PROG_OBJ = ${PROG_SRC:.c=.o}

all: ${LIB_NAME} ${LIBX_NAME} ${PROG_NAME}

.c.o:
	${GCC} ${FLAGS} -c $< -o ${<:.c=.o}

${LIB_NAME}:
	make -C Libft/

${LIBX_NAME}:
	make -C Minilibx/

${PROG_NAME}: ${PROG_OBJ}
	${GCC} ${FLAGS} -o ${PROG_NAME} ${PROG_OBJ} -L Libft/ -lft -L./Minilibx -lmlx -lXext -lX11

bonus: all

clean:
	make clean -C Libft/
	make clean -C Minilibx/
	rm -f ${PROG_OBJ}

fclean: clean
	make fclean -C Libft/
	rm -f ${PROG_NAME} ${LIB_NAME} ${LIBX_NAME}

re: fclean all
