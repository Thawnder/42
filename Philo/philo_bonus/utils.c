/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <bpleutin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:43:05 by bpleutin          #+#    #+#             */
/*   Updated: 2023/11/02 13:37:49 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_alltime	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

void	protected_print(t_philo *philo, int state)
{
	sem_wait(philo->info->s_state);
	philo->state = state;
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
	sem_post(philo->info->s_state);
}

void	*timer(void *ptr)
{
	t_philo	*p;

	p = (t_philo *)ptr;
	sem_wait(p->info->start);
	sem_post(p->info->start);
	while (!sem_wait(p->info->is_dead) && !p->is_dead
		&& !sem_wait(p->info->is_done) && !p->is_done
		&& !sem_wait(p->info->end) && !p->info->finished)
	{
		sem_post(p->info->is_done);
		sem_post(p->info->is_dead);
		sem_post(p->info->end);
		if (nostop(p) && !sem_wait(p->info->last)
			&& get_time() - p->last_meal > p->info->time_to_die + 1)
			return (sem_post(p->info->last), protected_print(p, DEAD),
				sem_post(p->info->forks), (void *)0);
		sem_post(p->info->last);
	}
	if (p->info->finished)
		sem_post(p->info->die);
	sem_post(p->info->is_done);
	sem_post(p->info->is_dead);
	sem_post(p->info->end);
	return ((void *)0);
}

void	init_sem(t_data *d)
{
	d->info.forks = sem_open("forks", O_CREAT | O_EXCL,
			0644, d->info.gang_len - 1);
	sem_post(d->info.forks);
	d->info.write = sem_open("write", O_CREAT | O_EXCL, 0644, 0);
	sem_post(d->info.write);
	d->info.start = sem_open("start", O_CREAT | O_EXCL, 0644, 0);
	sem_post(d->info.start);
	d->info.end = sem_open("end", O_CREAT | O_EXCL, 0644, 0);
	sem_post(d->info.end);
	d->info.die = sem_open("die", O_CREAT | O_EXCL, 0644, 0);
	sem_post(d->info.die);
	d->info.is_done = sem_open("is_done", O_CREAT | O_EXCL, 0644, 0);
	sem_post(d->info.is_done);
	d->info.is_dead = sem_open("is_dead", O_CREAT | O_EXCL, 0644, 0);
	sem_post(d->info.is_dead);
	d->info.last = sem_open("last", O_CREAT | O_EXCL, 0644, 0);
	sem_post(d->info.last);
	d->info.s_state = sem_open("state", O_CREAT | O_EXCL, 0644, 0);
	sem_post(d->info.s_state);
	d->info.meal = sem_open("meal", O_CREAT | O_EXCL, 0644, 0);
	sem_post(d->info.meal);
}

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}
