/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <bpleutin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:43:05 by bpleutin          #+#    #+#             */
/*   Updated: 2023/10/25 17:54:55 by bpleutin         ###   ########.fr       */
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
	else if (philo->state == DEAD && !philo->info->dead)
	{
		philo->info->dead = 1;
		sem_post(philo->info->die);
		printf("%llu philo %d is dead\n",
			get_time() - philo->info->start_time, philo->id + 1);
	}
	sem_post(philo->info->write);
}

void	*timer(void *ptr)
{
	t_data	*d;
	int		i;

	d = (t_data *)ptr;
	sem_wait(d->info.die);
	sem_wait(d->info.start);
	sem_post(d->info.start);
	while (!sem_wait(d->info.end)
		&& d->info.finished < d->info.gang_len)
	{
		sem_post(d->info.end);
		i = -1;
		while (++i < d->info.gang_len && !sem_wait(d->info.last))
		{
			if (nostop(&d->philo[i]) && get_time()
				- d->philo[i].last_meal > d->info.time_to_die + 1)
				return (sem_wait(d->info.s_state), d->philo[i].state = DEAD,
					sem_post(d->info.s_state),
					protected_print(&d->philo[i]),
					sem_post(d->info.last), (void *)0);
			sem_post(d->info.last);
		}
	}
	sem_post(d->info.end);
	return ((void *)0);
}
