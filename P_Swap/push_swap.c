/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:29:13 by bpleutin          #+#    #+#             */
/*   Updated: 2023/08/15 11:38:17 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	check_arg(char *arg, t_list *lst)
{
	int	i;

	i = 0;
	if ((arg[i] == '-' || arg[i] == '+') && !(arg[++i] >= '0' && arg[i] <= '9'))
	{
		free_list(&lst);
		print_error();
	}
	while (arg[i])
	{
		if (!(arg[i] >= '0' && arg[i] <= '9'))
		{
			free_list(&lst);
			print_error();
		}
		i++;
	}
}

int	check_nb(char *arg, t_list *lst)
{
	int	i;

	i = 0;
	if ((arg[i] == '-' || arg[i] == '+') && !(arg[++i] >= '0' && arg[i] <= '9'))
	{
		free_list(&lst);
		print_error();
	}
	while (arg[i] && !(arg[i] == 32 || (arg[i] >= 9 && arg[i] <= 13)))
	{
		if (!(arg[i] >= '0' && arg[i] <= '9'))
		{
			free_list(&lst);
			print_error();
		}
		i++;
	}
	if (arg[i] && !(arg[i] == 32 || (arg[i] >= 9 && arg[i] <= 13)))
	{
		free_list(&lst);
		print_error();
	}
	if (i == 0)
		exit(EXIT_FAILURE);
	return (i);
}

void	decompose_arg(char *arg, t_list **a)
{
	int	i;
	int	len;

	i = 0;
	while (arg[i] == 32 || (arg[i] >= 9 && arg[i] <= 13))
	{
		if (!arg[++i])
			print_error();
	}
	len = check_nb(&arg[i], *a);
	*a = ft_lstnew(ft_libatoi(&arg[i], a));
	i += len;
	while (arg[i])
	{
		if (arg[i] == 32 || (arg[i] >= 9 && arg[i] <= 13))
			i++;
		else
		{
			len = check_nb(&arg[i], *a);
			check_dup(*a, ft_libatoi(&arg[i], a));
			ft_lstadd_back(a, ft_lstnew(ft_libatoi(&arg[i], a)));
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
		check_arg(argv[i], *a);
		*a = ft_lstnew(ft_libatoi(argv[i++], a));
		while (i < argc)
		{
			check_arg(argv[i], *a);
			check_dup(*a, ft_libatoi(argv[i], a));
			ft_lstadd_back(a, ft_lstnew(ft_libatoi(argv[i], a)));
			i++;
		}
	}
	else
		decompose_arg(argv[i], a);
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
		check_arg(argv[i], *a);
		*a = ft_lstnew(ft_libatoi(argv[i++], a));
		while (i < argc)
		{
			check_arg(argv[i], *a);
			check_dup(*a, ft_libatoi(argv[i], a));
			ft_lstadd_back(a, ft_lstnew(ft_libatoi(argv[i], a)));
			i++;
		}
	}
	else
		decompose_arg(argv[i], a);
}
