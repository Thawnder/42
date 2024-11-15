/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <bpleutin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:21:20 by bpleutin          #+#    #+#             */
/*   Updated: 2024/11/15 11:53:53 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>

size_t	ft_strlen(const char *str);
char	*ft_strcpy(char *dest, const char *src);
int		ft_strcmp(const char *s1, const char *s2);
ssize_t	ft_read(int fd, void *buf, size_t count);
ssize_t ft_write(int fd, const void *buf, size_t count);
char	*ft_strdup(const char *s);

#define STRLEN(x)			printf("real[%ld]\nmine[%ld]\n\n", strlen(x), ft_strlen(x));
#define STRCPY(x1, x2, y)	printf("real[%s]\nmine[%s]\n\n", strcpy(x1, y), ft_strcpy(x2, y));
#define	STRCMP(x1, x2)		printf("real[%d] mine[%d]\n", strcmp(x1, x2), ft_strcmp(x1, x2));
#define READ(x, y1, y2, z)	printf("real[%ld]", read(x, y1, z)); printf("[%s][%d][%s]", y1, errno, strerror(errno));errno = 0; printf(" mine[%ld]", ft_read(x, y2, z)); printf("[%s][%d][%s]\n", y2, errno, strerror(errno));
#define WRITE(x, y, z)		write(x, y, z); printf("[%d][%s]\n", errno, strerror(errno)); ft_write(x, y, z); printf("[%d][%s]\n", errno, strerror(errno));
#define STRDUP(x)			tmp = strdup(x); printf("real[%s] ", tmp); free(tmp); tmp = ft_strdup(x); printf("mine[%s]\n", tmp); free(tmp);

int		main(void)
{
	char	tmp1[1000];
	char	tmp2[1000];
	char	*tmp;

	tmp1[999] = '\0';
	tmp2[999] = '\0';

	printf("*** strlen ***\n");
	STRLEN("j'aime trop l'assembleur");
	STRLEN("");
	STRLEN("zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz");
	STRLEN("blabla \0 de toute façon la fin est pas prise en compte je peux dire de la grosse D personne le verra");

	printf("\n*** strcpy ***\n");
	STRCPY(tmp1, tmp2, "j'aime trop l'assembleur");
	STRCPY(tmp1, tmp2, "");
	STRCPY(tmp1, tmp2, "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz");
	STRCPY(tmp1, tmp2, "blabla \0 de toute façon la fin est pas prise en compte je peux dire de la grosse D personne le verra");

	printf("\n*** strcmp ***\n");
	STRCMP("j'aime trop l'assembleur", "j'aime trop l'assembleur");
	STRCMP("", "j'aime trop l'assembleur");
	STRCMP("j'aime trop l'assembleur", "");
	STRCMP("", "");
	STRCMP("j'aime trop l'assembleur", "bonjour");
	STRCMP("aa", "az");

	printf("\n*** read ***\n");
	errno = 0;
	tmp1[5] = 0;
	tmp2[5] = 0;
	READ(0, tmp1, tmp2, 5);
	errno = 0;
	tmp1[4] = 0;
	tmp2[4] = 0;
	READ(0, tmp1, tmp2, 4);
	errno = 0;
	tmp1[0] = 0;
	tmp2[0] = 0;
	READ(0, tmp1, tmp2, 4);
	errno = 0;
	READ(456564654, tmp1, tmp2, 3);

	printf("\n*** write ***\n");
	errno = 0;
	WRITE(1, "j'aime trop l'assembleur", 24);
	WRITE(9324, "j'aime trop l'assembleur", 24);

	printf("\n*** strdup ***\n");
	STRDUP("j'aime trop l'assembleur");
	STRDUP("");
	STRDUP("zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz");
	STRDUP("blabla \0 de toute façon la fin est pas prise en compte je peux dire de la grosse D personne le verra");
}