MAKEFLAGS += --silent

NAME = libft.a
CLIENT_NAME = client
SERVER_NAME = server

GCC = cc
FLAGS = -Wall -Wextra -Werror -g

CLIENT_SRC = client.c
SERVER_SRC = server.c
OBJS_C = ${CLIENT_SRC:.c=.o}
OBJS_S = ${SERVER_SRC:.c=.o}

all: ${NAME} ${CLIENT_NAME} ${SERVER_NAME}

.c.o:
	${GCC} ${FLAGS} -c $< -o ${<:.c=.o}

${NAME}:
	make -C Libft/

${CLIENT_NAME}: ${OBJS_C}
	${GCC} ${FLAGS} -o ${CLIENT_NAME} ${OBJS_C} -L Libft/ -lft

${SERVER_NAME}: ${OBJS_S}
	${GCC} ${FLAGS} -o ${SERVER_NAME} ${OBJS_S} -L Libft/ -lft

bonus: all

clean:
	make clean -C Libft/
	rm -f ${OBJS_S} ${OBJS_C}

fclean: clean
	make fclean -C Libft/
	rm -f ${CLIENT_NAME} ${SERVER_NAME} ${NAME}

re: fclean all
