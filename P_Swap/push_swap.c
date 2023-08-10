/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:29:13 by bpleutin          #+#    #+#             */
/*   Updated: 2023/08/09 17:34:18 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	check_arg(char *arg, t_list *lst, int flag)
{
	int	i;

	i = 0;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i])
	{
		if (!(arg[i] >= '0' && arg[i] <= '9'))
		{
			free_list(&lst);
			print_error(flag);
		}
		i++;
	}
}

int	check_nb(char *arg, t_list *lst, int flag)
{
	int	i;

	i = 0;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i] && !(arg[i] == 32 || (arg[i] >= 9 && arg[i] <= 13)))
	{
		if (!(arg[i] >= '0' && arg[i] <= '9'))
		{
			free_list(&lst);
			print_error(flag);
		}
		i++;
	}
	if (arg[i] && !(arg[i] == 32 || (arg[i] >= 9 && arg[i] <= 13)))
	{
		free_list(&lst);
		print_error(flag);
	}
	return (i);
}

void	decompose_arg(char *arg, t_list **a, int flag)
{
	int	i;
	int	len;

	i = 0;
	if (!arg[i])
		print_error(flag);
	while (arg[i] == 32 || (arg[i] >= 9 && arg[i] <= 13))
		i++;
	len = check_nb(&arg[i], *a, flag);
	*a = ft_lstnew(ft_libatoi(&arg[i], flag));
	i += len;
	while (arg[i])
	{
		if (arg[i] == 32 || (arg[i] >= 9 && arg[i] <= 13))
			i++;
		else
		{
			len = check_nb(&arg[i], *a, flag);
			check_dup(*a, ft_libatoi(&arg[i], flag), flag);
			ft_lstadd_back(a, ft_lstnew(ft_libatoi(&arg[i], flag)));
			i += len;
		}
	}
}

void	init_all(int argc, char **argv, t_list **a, t_info **info)
{
	int	i;

	i = 1;
	*a = NULL;
	if (argc > 2)
	{
		check_arg(argv[i], *a, 0);
		*a = ft_lstnew(ft_libatoi(argv[i++], 0));
		while (i < argc)
		{
			check_arg(argv[i], *a, 0);
			check_dup(*a, ft_libatoi(argv[i], 0), 0);
			ft_lstadd_back(a, ft_lstnew(ft_libatoi(argv[i], 0)));
			i++;
		}
	}
	else
		decompose_arg(argv[i], a, 0);
	*info = ft_calloc(8, sizeof(t_list));
	(*info)->size_a = ft_lstsize(*a);
}

void	init_all_checker(int argc, char **argv, t_list **a)
{
	int	i;

	i = 1;
	*a = NULL;
	if (argc > 2)
	{
		check_arg(argv[i], *a, 1);
		*a = ft_lstnew(ft_libatoi(argv[i++], 1));
		while (i < argc)
		{
			check_arg(argv[i], *a, 1);
			check_dup(*a, ft_libatoi(argv[i], 1), 1);
			ft_lstadd_back(a, ft_lstnew(ft_libatoi(argv[i], 1)));
			i++;
		}
	}
	else
		decompose_arg(argv[i], a, 1);
}
