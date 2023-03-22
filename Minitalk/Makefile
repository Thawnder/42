CLIENT_NAME = client

SERVER_NAME = server

GCC = gcc

CLIENT_SRC = client.c

SERVER_SRC = server.c

FLAGS = -Wall -Wextra -Werror -g

OBJ_CLIENT = ${CLIENT_SRC:.c=.o}

OBJ_SERVER = ${SERVER_SRC:.c=.o}

all: ${CLIENT_NAME} ${SERVER_NAME}

.c.o:
	${GCC} ${FLAGS} -c $< -o ${<:.c=.o}

${CLIENT_NAME}: ${OBJ_CLIENT}
	${GCC} ${FLAGS} -o ${CLIENT_NAME} $^

${SERVER_NAME}: ${OBJ_SERVER}
	${GCC} ${FLAGS} -o ${SERVER_NAME} $^

bonus: all

clean:
	rm -f ${OBJ_SERVER}
	rm -f ${OBJ_CLIENT}

fclean: clean
	rm -f ${CLIENT_NAME}
	rm -f ${SERVER_NAME}

re: fclean all
