/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 16:29:48 by bpleutin          #+#    #+#             */
/*   Updated: 2023/08/10 17:08:33 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	get_idx(t_list *elt, t_list *lst)
{
	int	i;

	i = 1;
	while (lst && lst != elt)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

int	get_idx_from_data(int data, t_list *lst)
{
	int	i;

	i = 1;
	while (lst && lst->data != data)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

t_list	*get_elt_from_idx(int idx, t_list *lst)
{
	while (--idx)
		lst = lst->next;
	return (lst);
}

void	free_list(t_list **a)
{
	t_list	*tmp;

	if (a)
	{
		while (*a)
		{
			tmp = *a;
			*a = (*a)->next;
			tmp->next = NULL;
			free(tmp);
		}
	}
}

void	print_error(void)
{
	write(2, "Error\n", 6);
	exit(EXIT_FAILURE);
}
