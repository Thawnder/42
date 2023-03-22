/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:21:48 by bpleutin          #+#    #+#             */
/*   Updated: 2023/03/22 15:13:52 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_recv_msg(void)
{
	// lol
}

int	main(void)
{
	char	*pid;

	pid = ft_strdup(ft_itoa(getpid()));
	write(1, "PID: ", 5);
	write(1, pid, ft_strlen(pid));
	write(1, "\n", 1);
	pause();
	while (ft_recv_msg())
		pause();
	return (0);
}
