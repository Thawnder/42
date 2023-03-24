/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:21:48 by bpleutin          #+#    #+#             */
/*   Updated: 2023/03/24 16:48:27 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char	*ft_realloc(char *dest, int size)
{
	char	*tmp;

	tmp = ft_strdup(dest);
	free(dest);
	dest = malloc(ft_strlen(tmp) + size + 1);
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, tmp, ft_strlen(tmp) + 1);
	free(tmp);
	return (dest);
}

char	*ft_reallocat(char *dest, char src)
{
	int	i;

	i = 0;
	dest = ft_realloc(dest, 1);
	while (dest[i] != '\0')
		i++;
	dest[i] = src;
	i++;
	dest[i] = '\0';
	return (dest);
}

void	ft_recv_char(int signal, siginfo_t *s, void *osef)
{
	static int		i = 0;
	static char		c = 0;
	static char		*str = NULL;

	(void)osef;
	if (!str || !str[0])
		str = ft_libftcalloc(1, 1);
	if (i < 9)
	{
		if (signal == SIGUSR1)
			c = c | 1 << i;
		i++;
		return ;
	}
	str = ft_reallocat(str, c);
	// ft_printf("%c", c);
	i = 0;
	if (c == 0)
	{
		kill(s->si_pid, SIGUSR1);
		ft_printf("%s\n", str);
		// ft_printf("\n");
		return ;
	}
	c = 0;
}

int	main(void)
{
	struct sigaction	s;

	ft_printf("PID: %d\n", getpid());
	s.sa_sigaction = ft_recv_char;
	s.sa_flags = SA_SIGINFO | SA_RESTART;
	sigemptyset(&s.sa_mask);
	while (1)
	{
		sigaction(SIGUSR1, &s, 0);
		sigaction(SIGUSR2, &s, 0);
	}
	return (0);
}
