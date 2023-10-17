/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:33:21 by bpleutin          #+#    #+#             */
/*   Updated: 2023/10/17 18:11:32 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define START 0
# define EATING 1
# define SLEEPING 2
# define THINKING 3

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef unsigned long long int	t_alltime;

typedef struct s_info
{
	int				gang_size;
	int				nbr_of_meals;
	t_alltime		time_to_die;
	t_alltime		time_to_eat;
	t_alltime		time_to_sleep;
	t_alltime		start_time;
	pthread_mutex_t	write;
	pthread_mutex_t	*forks;
}		t_info;

typedef struct s_philo
{
	int				id;
	pthread_t		tid;
	t_alltime		last_meal;
	int				state;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	t_info			*info;
}		t_philo;

typedef struct s_data
{
	t_info		info;
	t_philo		*philo;
	pthread_t	timer_tid;
}		t_data;

void	set_philo(void *ptr);
void	timer(void *ptr);

#endif
