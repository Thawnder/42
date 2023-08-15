/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_instructions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 14:14:48 by bpleutin          #+#    #+#             */
/*   Updated: 2023/08/10 17:24:29 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	do_both(t_list **a, t_list **b, int flag)
{
	if (flag == 1)
	{
		do_rotate(a);
		do_rotate(b);
	}
	else
	{
		do_rrotate(a);
		do_rrotate(b);
	}
}

void	do_swap(t_list **lst)
{
	t_list	*tmp;

	if (*lst && (*lst)->next)
	{
		tmp = (*lst)->next;
		(*lst)->next = tmp->next;
		tmp->next = *lst;
		*lst = tmp;
	}
}

void	do_push(t_list **dest, t_list **src)
{
	t_list	*tmp;

	if (*src)
	{
		tmp = *src;
		*src = (*src)->next;
		tmp->next = *dest;
		*dest = tmp;
	}
}

void	do_rotate(t_list **lst)
{
	t_list	*tmp;

	if (*lst)
	{
		tmp = *lst;
		*lst = tmp->next;
		while ((*lst)->next)
			*lst = (*lst)->next;
		(*lst)->next = tmp;
		*lst = tmp->next;
		tmp->next = NULL;
	}
}

void	do_rrotate(t_list **lst)
{
	t_list	*tmp;

	if (*lst && (*lst)->next)
	{
		tmp = *lst;
		while (tmp->next->next)
			tmp = tmp->next;
		tmp->next->next = *lst;
		*lst = tmp->next;
		tmp->next = NULL;
	}
}
