/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:21:33 by bpleutin          #+#    #+#             */
/*   Updated: 2023/03/22 15:00:03 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_send_msg(int pid, char *msg)
{
	// send msg to server
	if (!ft_strncmp(msg, "exit", ft_strlen(msg)))
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	if (argc != 3 || !argv[2])
		return (-1);
	// init signals
	while (ft_send_msg(ft_atoi(argv[1]), argv[2]))
		pause();
	return (0)
}
