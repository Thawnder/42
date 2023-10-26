/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <bpleutin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:43:05 by bpleutin          #+#    #+#             */
/*   Updated: 2023/10/26 15:14:00 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_alltime	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

void	protected_print(t_philo *philo)
{
	sem_wait(philo->info->write);
	if (philo->state == EATING)
		printf("%llu philo %d is eating\n",
			get_time() - philo->info->start_time, philo->id + 1);
	else if (philo->state == SLEEPING)
		printf("%llu philo %d is sleeping\n",
			get_time() - philo->info->start_time, philo->id + 1);
	else if (philo->state == THINKING)
		printf("%llu philo %d is thinking\n",
			get_time() - philo->info->start_time, philo->id + 1);
	else if (philo->state == DEAD)
	{
		sem_post(philo->info->die);
		printf("%llu philo %d is dead\n",
			get_time() - philo->info->start_time, philo->id + 1);
		return ;
	}
	sem_post(philo->info->write);
}

void	*timer(void *ptr) // loop toujours...
{
	t_philo	*p;

	p = (t_philo *)ptr;
	sem_wait(p->info->start);
	sem_post(p->info->start);
	while (!sem_wait(p->info->end) && p->info->finished < p->info->gang_len)
	{
		sem_post(p->info->end);
		if (!sem_wait(p->info->last) && nostop(p)
			&& get_time() - p->last_meal > p->info->time_to_die + 1)
			return (sem_wait(p->info->s_state), p->state = DEAD,
				sem_post(p->info->s_state),
				protected_print(p),
				sem_post(p->info->last), (void *)0);
		sem_post(p->info->last);
	}
	sem_post(p->info->end);
	return ((void *)0);
}
