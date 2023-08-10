MAKEFLAGS += --silent

LIB_NAME = libft.a
PROG_NAME = push_swap
BONUS_NAME = checker

GCC = cc
FLAGS = -Wall -Wextra -Werror -g

PROG_SRC = 	push_swap.c \
		new_atoi.c \
		checker.c \
		checker_instructions.c \
		instructions.c \
		lst_utils.c \
		lst_utils2.c \
		sort_three.c \
		sort_main.c \
		main.c \

BONUS_SRC =	checker.c \
		new_atoi.c \
		checker_instructions.c \
		push_swap.c \
		instructions.c \
		lst_utils.c \
		lst_utils2.c \
		sort_three.c \
		sort_main.c \
		checker_main.c \

PROG_OBJ = ${PROG_SRC:.c=.o}

BONUS_OBJ = ${BONUS_SRC:.c=.o}

all: ${LIB_NAME} ${PROG_NAME} ${BONUS_NAME}

.c.o:
	${GCC} ${FLAGS} -c $< -o ${<:.c=.o}

${LIB_NAME}:
	make -C Libft/

${PROG_NAME}: ${PROG_OBJ}
	${GCC} ${FLAGS} -o ${PROG_NAME} ${PROG_OBJ} -L Libft/ -lft

bonus: ${LIB_NAME} ${BONUS_NAME}

${BONUS_NAME}: ${BONUS_OBJ}
	${GCC} ${FLAGS} -o ${BONUS_NAME} ${BONUS_OBJ} -L Libft/ -lft

clean:
	make clean -C Libft/
	rm -f ${PROG_OBJ} ${BONUS_OBJ}

fclean: clean
	make fclean -C Libft/
	rm -f ${PROG_NAME} ${BONUS_NAME} ${LIB_NAME}

re: fclean all
