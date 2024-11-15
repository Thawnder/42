NAME = libasm.a
TEST = test
TEST_BONUS = test_bonus

NA = nasm
NA_FLAGS = -f elf64

CC = gcc
CC_FLAGS = -Wall -Werror -Wextra

SRC = 	ft_strlen.s \
		ft_strcpy.s \
		ft_strcmp.s \
		ft_write.s \
		ft_read.s \
		ft_strdup.s

# BONUS_SRC = 	ft_atoi_base.s \
# 				ft_list_push_front.s \
# 				ft_list_size.s \
# 				ft_list_sort.s \
# 				ft_list_remove_if.s \

OBJ	=		${SRC:.s=.o}

# BONUS_OBJ = ${BONUS_SRC:.s=.o}

%.o: 		%.s
					${NA} ${NA_FLAGS} $<

all: 		${NAME}

${NAME}: 	${OBJ}
					ar rcs ${NAME} ${OBJ}

test: 		${NAME}
					${CC} ${FLAGS} main.c -L. -lasm -o ${TEST}
					./${TEST} < Makefile


# bonus: 		${OBJ} ${BONUS_OBJ}
# 					ar rcs ${NAME} ${OBJ} ${BONUS_OBJ}

# test_bonus:	bonus
# 					${CC} ${FLAGS} main_bonus.c -L. -lasm -o ${TEST_BONUS}
# 					./${TEST_BONUS}

clean:
					rm -rf ${OBJ} ${BONUS_OBJ}

fclean: 	clean
					rm -rf ${NAME} ${TEST}

re: 		fclean all

.PHONY:		all bonus clean fclean re test test_bonus
