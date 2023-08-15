/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_atoi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 17:29:15 by bpleutin          #+#    #+#             */
/*   Updated: 2023/08/10 17:20:10 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	free_buffers(char *buf, char *tmp)
{
	free(buf);
	free(tmp);
	return (1);
}

int	check_int(const char *nptr, int i, int sign)
{
	int	len;

	len = 0;
	while (nptr[len] >= '0' && nptr[len] <= '9')
		len++;
	if ((len > 10)
		|| (len == 10 
			&& (nptr[i] > '2' || nptr[i + 1] > '1' || nptr[i + 2] > '4'
				|| nptr[i + 3] > '7' || nptr[i + 4] > '4' || nptr[i + 5] > '8'
				|| nptr[i + 6] > '3' || nptr[i + 7] > '6' || nptr[i + 8] > '4'
				|| ((sign == 1 && nptr[i + 9] > '7') 
					|| (sign == -1 && nptr[i + 9] > '8')))))
		return (0);
	return (1);
}

int	ft_libatoi(const char *nptr, t_list **a)
{
	int				i;
	int				sign;
	unsigned int	res;

	i = 0;
	sign = 1;
	res = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i++] == '-')
			sign *= -1;
	}
	if ((nptr[i] == '-' || nptr[i] == '+') || (!check_int(&nptr[i], 0, sign)))
	{
		free_list(a);
		print_error();
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = res * 10 + nptr[i] - 48;
		i++;
	}
	return ((int)res * sign);
}
