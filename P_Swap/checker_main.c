/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 16:54:53 by bpleutin          #+#    #+#             */
/*   Updated: 2023/08/09 18:31:22 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_list	*a;
	t_list	*b;
	int		size;

	if (argc < 2)
	{
		checker(argc, NULL, NULL);
		exit(EXIT_FAILURE);
	}
	b = NULL;
	init_all_checker(argc, argv, &a);
	size = ft_lstsize(a);
	checker(argc, &a, &b);
	if (b || ft_lstsize(a) != size || !is_sorted(a))
		ft_printf("KO\n");
	else
		ft_printf("OK\n");
	free_all(&a, &b);
	return (0);
}
