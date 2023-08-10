/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 14:14:48 by bpleutin          #+#    #+#             */
/*   Updated: 2023/07/27 17:30:02 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	print_previous(t_info *info)
{
	if (info->prev == 1 || info->prev == 2)
		ft_printf("r%c\n", info->prev + 'a' - 1);
	else if (info->prev == 3 || info->prev == 4)
		ft_printf("rr%c\n", info->prev + 'a' - 3);
}

void	ft_swap(t_list **lst, t_info **info, char c)
{
	t_list	*tmp;

	if (*lst && (*lst)->next)
	{
		tmp = (*lst)->next;
		(*lst)->next = tmp->next;
		tmp->next = *lst;
		*lst = tmp;
		print_previous(*info);
		ft_printf("s%c\n", c);
		(*info)->prev = c - 'a' + 7;
	}
}

void	ft_push(t_list **dest, t_list **src, t_info **info, char c)
{
	t_list	*tmp;

	if (*src)
	{
		tmp = *src;
		*src = (*src)->next;
		tmp->next = *dest;
		*dest = tmp;
		print_previous(*info);
		ft_printf("p%c\n", c);
		(*info)->prev = c - 'a' + 5;
		if (c == 'a')
		{
			(*info)->size_a++;
			(*info)->size_b--;
		}
		else
		{
			(*info)->size_a--;
			(*info)->size_b++;
		}
	}
}

void	ft_rotate(t_list **lst, t_info **info, char c)
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
		if ((c == 'b' && (*info)->prev == RA)
			|| (c == 'a' && (*info)->prev == RB))
		{
			(*info)->prev = 0;
			ft_printf("rr\n");
		}
		else
		{
			print_previous(*info);
			(*info)->prev = c - 'a' + 1;
		}
	}
}

void	ft_rrotate(t_list **lst, t_info **info, char c)
{
	t_list	*tmp;

	if (*lst)
	{
		tmp = *lst;
		while (tmp->next->next)
			tmp = tmp->next;
		tmp->next->next = *lst;
		*lst = tmp->next;
		tmp->next = NULL;
		if ((c == 'b' && (*info)->prev == RRA)
			|| (c == 'a' && (*info)->prev == RRB))
		{
			(*info)->prev = 0;
			ft_printf("rrr\n");
		}
		else
		{
			print_previous(*info);
			(*info)->prev = c - 'a' + 3;
		}
	}
}
