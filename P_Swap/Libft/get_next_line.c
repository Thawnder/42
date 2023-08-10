/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:15:07 by bpleutin          #+#    #+#             */
/*   Updated: 2023/08/08 11:38:39 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_cut_line(char *str, char *line)
{
	char	*res;
	int		n;

	res = NULL;
	n = ft_strlen(str);
	if (!line || !line[n])
	{
		free(line);
		return (res);
	}
	if (line[n])
		res = ft_substr(line, n, ft_strlen(line) - n);
	free(line);
	return (res);
}

static char	*ft_read_line(int fd, char *line, char **res)
{
	char	*buffer;
	int		r;
	int		n;

	buffer = malloc(BUFFER_SIZE + 1);
	r = 1;
	while (r != 0 && !ft_strchr(line, '\n'))
	{
		r = read(fd, buffer, BUFFER_SIZE);
		buffer[r] = '\0';
		line = ft_strjoin(line, buffer);
	}
	free(buffer);
	n = 0;
	if (line && line[n] && !*res)
	{
		while (line[n] && line[n] != '\n')
			n++;
		*res = ft_substr(line, 0, n + 1);
	}
	else
		*res = NULL;
	line = ft_cut_line(*res, line);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*line = NULL;
	char		*res;

	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, 0, 0) < 0)
		return (NULL);
	res = NULL;
	line = ft_read_line(fd, line, &res);
	return (res);
}
