/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:21:33 by bpleutin          #+#    #+#             */
/*   Updated: 2023/04/12 14:58:11 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_re;

void	ft_kill(char c, int pid)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		g_re = 0;
		if (c & (1 << i))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		i++;
		while (g_re != 1)
			usleep(1);
	}
}

void	ft_send_msg(int pid, char *msg)
{
	int	i;

	i = 0;
	if (kill(pid, 0) < 0)
	{
		ft_printf("It ain't workin'\n");
		exit(EXIT_FAILURE);
	}
	while (msg[i])
		ft_kill(msg[i++], pid);
	ft_kill(msg[i], pid);
}

void	ft_confirm(int signal)
{
	if (signal == SIGUSR1)
		g_re = 1;
	else
	{
		ft_printf("Message recu par le serveur\n");
		exit(EXIT_SUCCESS);
	}
}

int	main(int argc, char **argv)
{
	int	pid;

	if (argc != 3 || !argv[2])
	{
		ft_printf("Wrong format. Format should be: ./client [PID] [Message]\n");
		exit(EXIT_FAILURE);
	}
	signal(SIGUSR1, &ft_confirm);
	signal(SIGUSR2, &ft_confirm);
	pid = ft_libatoi(argv[1]);
	if (pid <= 0)
	{
		ft_printf("Invalid PID\n");
		exit(EXIT_FAILURE);
	}
	ft_send_msg(pid, argv[2]);
}
