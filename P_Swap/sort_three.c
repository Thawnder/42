/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_three.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:51:05 by bpleutin          #+#    #+#             */
/*   Updated: 2023/08/03 15:22:34 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	update_minmax(t_list *lst, t_info **info)
{
	(*info)->max = lst->data;
	(*info)->min = lst->data;
	while (lst)
	{
		if (lst->data > (*info)->max)
			(*info)->max = lst->data;
		else if (lst->data < (*info)->min)
			(*info)->min = lst->data;
		lst = lst->next;
	}
}

void	sort_three(t_list **lst, t_info **info)
{
	update_minmax(*lst, info);
	if ((*lst)->data == (*info)->min)
	{
		if ((*lst)->next->data == (*info)->max)
		{
			ft_rrotate(lst, info, 'a');
			ft_swap(lst, info, 'a');
		}
	}
	else if ((*lst)->data == (*info)->max)
	{
		ft_rotate(lst, info, 'a');
		if ((*lst)->data != (*info)->min)
			ft_swap(lst, info, 'a');
	}
	else
	{
		if ((*lst)->next->data == (*info)->min)
			ft_swap(lst, info, 'a');
		else
			ft_rrotate(lst, info, 'a');
	}
}

void	ft_back_b(t_list **a, t_list **b, t_info **info)
{
	int	i;

	i = 3;
	if ((*a)->data > (*b)->data)
	{
		while ((*b)->data != (*info)->max_b)
			ft_push(a, b, info, 'a');
	}
	while ((*b)->data != (*info)->max_b)
	{
		while (i > 0 && ft_lstlast(*a)->data > (*b)->data)
		{
			ft_rrotate(a, info, 'a');
			i--;
		}
		ft_push(a, b, info, 'a');
	}
	while (ft_lstlast(*a)->data < (*a)->data)
		ft_rrotate(a, info, 'a');
}

void	ft_back_bis(t_list **a, t_list **b, t_info **info)
{
	int	i;

	i = (*info)->start_nb;
	if ((*a)->data > (*b)->data)
	{
		while ((*info)->size_b)
			ft_push(a, b, info, 'a');
	}
	while ((*info)->size_b)
	{
		while (i > 0 && ft_lstlast(*a)->data > (*b)->data)
		{
			ft_rrotate(a, info, 'a');
			i--;
		}
		ft_push(a, b, info, 'a');
	}
	while (ft_lstlast(*a)->data < (*a)->data)
		ft_rrotate(a, info, 'a');
}

void	partial_sort(t_list **a, t_list **b, t_info **info)
{
	(*info)->max_b = (*info)->max;
	while ((*info)->size_a > 3)
	{
		update_minmax(*a, info);
		while ((*a)->data != (*info)->min)
		{
			if (get_idx_from_data((*info)->min, *a) <= (*info)->size_a / 2)
				ft_rotate(a, info, 'a');
			else
				ft_rrotate(a, info, 'a');
		}
		ft_push(b, a, info, 'b');
	}
	sort_three(a, info);
	while ((*b)->data != (*info)->max_b)
		ft_back_b(a, b, info);
}
