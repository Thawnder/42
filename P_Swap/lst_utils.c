/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 11:52:09 by bpleutin          #+#    #+#             */
/*   Updated: 2023/08/10 16:53:35 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_list	*ft_lstnew(int data)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->data = data;
	new->next = NULL;
	return (new);
}

void	check_dup(t_list *lst, int tofind)
{
	t_list	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (tmp->data == tofind)
		{
			free_list(&lst);
			print_error();
		}
		tmp = tmp->next;
	}
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (new && lst)
	{
		if (*lst)
		{
			last = *lst;
			while (last->next)
				last = last->next;
			last->next = new;
		}
		else
			*lst = new;
	}
}

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
