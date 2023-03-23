NAME = libft.a
CLIENT_NAME = client
SERVER_NAME = server

GCC = gcc
FLAGS = -Wall -Wextra -Werror -g

CLIENT_SRC = client.c
SERVER_SRC = server.c

all: ${NAME} ${CLIENT_NAME} ${SERVER_NAME}

.c.o:
	${GCC} ${FLAGS} -c $< -o ${<:.c=.o}

${NAME}:
	make -C Libft/
	cp Libft/libft.a .
	ar rc ${NAME}

${CLIENT_NAME}: ${NAME}
	${GCC} ${FLAGS} -o ${CLIENT_NAME} ${CLIENT_SRC} ${NAME}

${SERVER_NAME}: ${NAME}
	${GCC} ${FLAGS} -o ${SERVER_NAME} ${SERVER_SRC} ${NAME}

bonus: all

clean:
	make clean -C Libft/

fclean: clean
	make fclean -C Libft/
	rm -f ${CLIENT_NAME} ${SERVER_NAME} ${NAME}

re: fclean all
