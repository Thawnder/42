/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:21:33 by bpleutin          #+#    #+#             */
/*   Updated: 2023/03/23 16:22:54 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_re = 0;

void	ft_kill(char *msg, int i, int j, int pid)
{
	usleep(25);
	if (msg[i] & (1 << j))
		kill(pid, SIGUSR1);
	else
		kill(pid, SIGUSR2);
}

void	ft_send_msg(int pid, char *msg)
{
	int	i;
	int	j;

	i = 0;
	while (msg[i])
	{
		j = 0;
		while (j < 9)
			ft_kill(msg, i, j++, pid);
		usleep(5);
		kill(pid, SIGUSR1);
		i++;
	}
	j = 0;
	while (j < 9)
		ft_kill(msg, i, j++, pid);
	usleep(5);
	kill(pid, SIGUSR1);
}

void	ft_confirm(int signal)
{
	if (signal == SIGUSR1)
	{
		g_re = 1;
		ft_printf("Message recu par le serveur");
	}
	else
		g_re = 0;
}

int	main(int argc, char **argv)
{
	if (argc != 3 || !argv[2])
	{
		ft_printf("Wrong format. Format should be: ./client [PID] [Message]\n");
		return (-1);
	}
	ft_send_msg(ft_libatoi(argv[1]), argv[2]);
	while (g_re == 0)
		signal(SIGUSR1, ft_confirm);
	return (0);
}
