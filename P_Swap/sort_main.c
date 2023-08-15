/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:36:49 by bpleutin          #+#    #+#             */
/*   Updated: 2023/08/10 17:01:45 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	get_final_idx(t_list *elt, t_list *lst, t_info *info)
{
	int	i;

	i = 1;
	if (elt->data > lst->data && elt->data < ft_lstlast(lst)->data)
		return (i);
	while (lst)
	{
		if (elt->data > info->max && lst->data == info->max)
			return (i);
		if (elt->data < info->min && lst->data == info->min)
			return (++i);
		if (elt->data < lst->data && elt->data > lst->next->data)
			return (++i);
		lst = lst->next;
		i++;
	}
	return (i);
}

int	get_moves_nb(t_list *elt, t_list *a, t_list *b, t_info *info)
{
	int	nb_moves_a;
	int	nb_moves_b;

	if (get_idx(elt, a) <= info->size_a / 2)
	{
		if (get_final_idx(elt, b, info) <= ft_lstsize(b) / 2)
			return (ft_max(get_final_idx(elt, b, info), get_idx(elt, a)));
		nb_moves_a = get_idx(elt, a) - 1;
		nb_moves_b = ft_lstsize(b) - get_final_idx(elt, b, info) + 1;
	}
	else
	{
		if (get_final_idx(elt, b, info) > ft_lstsize(b) / 2)
			return (ft_max(ft_lstsize(b) - get_final_idx(elt, b, info),
					ft_lstsize(a) - get_idx(elt, a) + 1));
		nb_moves_a = ft_lstsize(a) - get_idx(elt, a) + 1;
		nb_moves_b = get_final_idx(elt, b, info) - 1;
	}
	return (nb_moves_a + nb_moves_b);
}

void	choose_best(t_list *a, t_list *b, t_info **info)
{
	int		i;
	int		min;
	t_list	*tmp;

	min = get_moves_nb(a, a, b, *info);
	(*info)->best = a;
	tmp = a;
	i = 0;
	while (++i < min && tmp->next)
	{
		if ((get_moves_nb(tmp->next, a, b, *info)) < min)
		{
			min = get_moves_nb(tmp->next, a, b, *info);
			(*info)->best = tmp->next;
		}
		if (get_moves_nb(get_elt_from_idx((*info)->size_a - i + 1, a),
				a, b, *info) < min)
		{
			min = get_moves_nb(get_elt_from_idx((*info)->size_a - i + 1, a),
					a, b, *info);
			(*info)->best = get_elt_from_idx((*info)->size_a - i + 1, a);
		}
		tmp = tmp->next;
	}
	(*info)->idx_best = get_idx((*info)->best, a);
}

void	push_best(t_list **a, t_list **b, t_info **info)
{
	if ((*info)->idx_final > (*info)->size_b)
		(*info)->idx_final = 1;
	while (*a != (*info)->best || (*info)->idx_final != 1)
	{
		if (*a != (*info)->best)
		{
			if (get_idx((*info)->best, *a) <= (*info)->size_a / 2)
				ft_rotate(a, info, 'a');
			else
				ft_rrotate(a, info, 'a');
		}
		if ((*info)->idx_final != 1)
		{
			if ((*info)->idx_final <= (*info)->size_b / 2
				&& (*info)->idx_final--)
				ft_rotate(b, info, 'b');
			else if ((*info)->idx_final > (*info)->size_b / 2
				&& (*info)->idx_final++)
				ft_rrotate(b, info, 'b');
			if ((*info)->idx_final > (*info)->size_b)
				(*info)->idx_final = 1;
		}
	}
	ft_push(b, a, info, 'b');
}

void	sort_main(t_list **a, t_list **b, t_info **info)
{
	ft_push(b, a, info, 'b');
	ft_push(b, a, info, 'b');
	while ((*info)->size_a > (*info)->start_nb)
	{
		update_minmax(*b, info);
		choose_best(*a, *b, info);
		(*info)->idx_final = get_final_idx((*info)->best, *b, *info);
		push_best(a, b, info);
	}
	update_minmax(*b, info);
	while ((*b)->data != (*info)->max)
	{
		if (get_idx_from_data((*info)->max, *b) <= (*info)->size_b / 2)
			ft_rotate(b, info, 'b');
		else
			ft_rrotate(b, info, 'b');
	}
	partial_sort(a, b, info);
	ft_back_bis(a, b, info);
	update_minmax(*a, info);
	while ((*a)->data != (*info)->min)
		ft_rrotate(a, info, 'a');
}
