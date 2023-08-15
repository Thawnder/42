/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:43:31 by bpleutin          #+#    #+#             */
/*   Updated: 2023/08/10 17:07:42 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_list	*a;
	t_info	*info;
	t_list	*b;

	if (argc < 2)
		exit(EXIT_FAILURE);
	init_all(argc, argv, &a, &info);
	b = NULL;
	if (info->size_a == 2 && a->data > a->next->data)
		ft_swap(&a, &info, 'a');
	else if (info->size_a == 3)
		sort_three(&a, &info);
	else if (!is_sorted(a))
	{
		info->start_nb = ft_max(3, (ft_lstsize(a) / 100) * 6);
		sort_main(&a, &b, &info);
	}
	print_previous(info);
	free_list(&a);
	free(info);
	return (0);
}
