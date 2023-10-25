/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <bpleutin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:33:21 by bpleutin          #+#    #+#             */
/*   Updated: 2023/10/25 18:13:32 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# define START 0
# define EATING 1
# define SLEEPING 2
# define THINKING 3
# define DEAD 4

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <signal.h>
# include <pthread.h>
# include <semaphore.h>

typedef unsigned long long int	t_alltime;

typedef struct s_info
{
	int				gang_len;
	int				max_meals;
	int				dead;
	int				finished;
	t_alltime		time_to_die;
	t_alltime		time_to_eat;
	t_alltime		time_to_sleep;
	t_alltime		start_time;
	sem_t			*forks;
	sem_t			*write;
	sem_t			*start;
	sem_t			*end;
	sem_t			*is_dead;
	sem_t			*die;
	sem_t			*last;
	sem_t			*meal;
	sem_t			*s_state;
}		t_info;

typedef struct s_philo
{
	int				id;
	int				is_dead;
	pid_t			pid;
	t_alltime		last_meal;
	int				state;
	int				meals;
	pthread_t		test_death;
	t_info			*info;
}		t_philo;

typedef struct s_data
{
	t_info		info;
	t_philo		*philo;
	pthread_t	timer_tid;
}		t_data;

int			nostop(t_philo *philo);	
void		set_philo(t_philo *philo);
void		*timer(void *ptr);
t_alltime	get_time(void);
void		protected_print(t_philo *philo);

#endif
