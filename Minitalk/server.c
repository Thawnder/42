/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:21:48 by bpleutin          #+#    #+#             */
/*   Updated: 2023/04/12 16:03:50 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char	*ft_realloc(char *dest, int size)
{
	char	*tmp;
	int		len;

	len = ft_strlen(dest);
	tmp = malloc(len + size + 1);
	if (!tmp)
		return (NULL);
	ft_memcpy(tmp, dest, len + 1);
	free(dest);
	return (tmp);
}

char	*ft_reallocat(char *dest, char c)
{
	int	i;

	if (!dest)
		dest = ft_calloc(1, 1);
	i = ft_strlen(dest);
	if (i % 100 == 0)
		dest = ft_realloc(dest, 100);
	dest[i] = c;
	i++;
	dest[i] = '\0';
	return (dest);
}

void	ft_recv_char(int signal, siginfo_t *s, void *idc)
{
	static int		i = 0;
	static char		c = 0;
	static char		*str = NULL;

	(void)idc;
	if (i < 8)
	{
		c = c | (signal == SIGUSR1) << i;
		if (++i < 8)
			kill(s->si_pid, SIGUSR1);
		if (i < 8)
			return ;
	}
	str = ft_reallocat(str, c);
	i = 0;
	if (c == 0)
	{
		kill(s->si_pid, SIGUSR2);
		ft_printf("%s, taille: %d\n", str, ft_strlen(str));
		free(str);
		str = NULL;
		return ;
	}
	kill(s->si_pid, SIGUSR1);
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
