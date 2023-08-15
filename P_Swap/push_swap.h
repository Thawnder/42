/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:27:40 by bpleutin          #+#    #+#             */
/*   Updated: 2023/08/10 17:19:13 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# define RA 1
# define RB 2
# define RRA 3
# define RRB 4
# define PA 5
# define PB 6
# define SA 7
# define SB 8

# include "Libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct s_list
{
	int				data;
	struct s_list	*next;
}		t_list;

typedef struct s_info
{
	int		prev;
	int		start_nb;
	int		min;
	int		max;
	int		max_b;
	t_list	*best;
	int		idx_best;
	int		idx_final;
	int		size_a;
	int		size_b;
}		t_info;

void	init_all(int argc, char **argv, t_list **a, t_info **info);
void	init_all_checker(int argc, char **argv, t_list **a);
t_list	*ft_lstnew(int content);
void	decompose_arg(char *arg, t_list **a);
void	check_arg(char *arg, t_list *lst);
int		check_nb(char *arg, t_list *lst);
void	check_dup(t_list *lst, int tofind);
void	ft_lstadd_back(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
int		get_idx(t_list *elt, t_list *lst);
int		get_idx_from_data(int data, t_list *lst);
t_list	*get_elt_from_idx(int idx, t_list *lst);
void	print_previous(t_info *info);
void	ft_swap(t_list **lst, t_info **info, char c);
void	do_swap(t_list **lst);
void	ft_push(t_list **dest, t_list **src, t_info **info, char c);
void	do_push(t_list **dest, t_list **src);
void	ft_rotate(t_list **lst, t_info **info, char c);
void	do_rotate(t_list **lst);
void	ft_rrotate(t_list **lst, t_info **info, char c);
void	do_rrotate(t_list **lst);
void	do_both(t_list **a, t_list **b, int flag);
void	update_minmax(t_list *lst, t_info **info);
void	sort_three(t_list **lst, t_info **info);
void	partial_sort(t_list **a, t_list **b, t_info **info);
int		get_final_idx(t_list *elt, t_list *lst, t_info *info);
void	free_list(t_list **a);
void	checker(t_list **a, t_list **b);
void	print_error(void);
int		free_all(t_list **a, t_list **b);
int		free_buffers(char *buf, char *tmp);
char	*ft_realloc(char *dest, char src, int size);
int		parse(t_list **a, t_list **b, char *buf);
int		is_sorted(t_list *a);
void	sort_main(t_list **a, t_list **b, t_info **info);
void	ft_back_b(t_list **a, t_list **b, t_info **info);
void	ft_back_bis(t_list **a, t_list **b, t_info **info);
int		ft_libatoi(const char *nptr, t_list **a);

#endif
