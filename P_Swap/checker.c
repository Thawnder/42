/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 14:53:12 by bpleutin          #+#    #+#             */
/*   Updated: 2023/08/10 17:08:58 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	free_all(t_list **a, t_list **b)
{
	free_list(a);
	free_list(b);
	return (1);
}

int	is_sorted(t_list *a)
{
	while (a->next)
	{
		if (a->data > a->next->data)
			return (0);
		a = a->next;
	}
	return (1);
}

int	parse(t_list **a, t_list **b, char *buf)
{
	if (buf[0] == 'r' && buf[1] == 'a' && buf[2] == '\n')
		do_rotate(a);
	else if (buf[0] == 'r' && buf[1] == 'b' && buf[2] == '\n')
		do_rotate(b);
	else if (buf[0] == 'r' && buf[1] == 'r' && buf[2] == '\n')
		do_both(a, b, 1);
	else if (buf[0] == 'r' && buf[1] == 'r' && buf[2] == 'a' && buf[3] == '\n')
		do_rrotate(a);
	else if (buf[0] == 'r' && buf[1] == 'r' && buf[2] == 'b' && buf[3] == '\n')
		do_rrotate(b);
	else if (buf[0] == 'r' && buf[1] == 'r' && buf[2] == 'r' && buf[3] == '\n')
		do_both(a, b, 2);
	else if (buf[0] == 's' && buf[1] == 'a' && buf[2] == '\n')
		do_swap(a);
	else if (buf[0] == 's' && buf[1] == 'b' && buf[2] == '\n')
		do_swap(b);
	else if (buf[0] == 'p' && buf[1] == 'a' && buf[2] == '\n')
		do_push(a, b);
	else if (buf[0] == 'p' && buf[1] == 'b' && buf[2] == '\n')
		do_push(b, a);
	else if (free_all(a, b))
		return (-1);
	return (0);
}

char	*ft_realloc(char *dest, char src, int size)
{
	char	*tmp;
	int		len;

	len = ft_strlen(dest);
	tmp = ft_calloc(len + size + 1, sizeof(char));
	if (!tmp)
		return (NULL);
	tmp = ft_memcpy(tmp, dest, len);
	tmp[ft_strlen(tmp)] = src;
	free(dest);
	return (tmp);
}

void	checker(t_list **a, t_list **b)
{
	char	*buf;
	char	*tmp;
	int		debut;

	debut = 0;
	buf = ft_calloc(2, 1);
	tmp = ft_calloc(1, 1);
	while (read(0, buf, 1))
	{
		tmp = ft_realloc(tmp, buf[0], 1);
		if (tmp[ft_strlen(tmp) - 1] == '\n')
		{
			if (parse(a, b, &tmp[debut]) == -1 && free_buffers(buf, tmp))
				print_error();
			debut = ft_strlen(tmp);
		}
	}
	free_buffers(buf, tmp);
}
