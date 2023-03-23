/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:21:48 by bpleutin          #+#    #+#             */
/*   Updated: 2023/03/23 16:22:34 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_recv_char(int signal, siginfo_t *s, void *osef)
{
	static int		i = 0;
	static char		c = 0;

	(void)osef;
	if (i < 9)
	{
		if (signal == SIGUSR1)
			c = c | 1 << i;
		i++;
		return ;
	}
	ft_printf("%c", c);
	i = 0;
	if (c == 0)
	{
		kill(s->si_pid, SIGUSR1);
		ft_printf("\n");
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
