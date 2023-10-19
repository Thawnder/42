/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <bpleutin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:50:07 by bpleutin          #+#    #+#             */
/*   Updated: 2023/10/19 12:46:54 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*timer(void *ptr)
{
	t_data	*data;
	int		i;

	data = (t_data *)ptr;
	while (1)
	{
		i = -1;
		while (++i < data->info.gang_size)
		{
			pthread_mutex_lock(&data->philo[i].lastmeal);
			if (get_time() - data->philo[i].last_meal >= data->info.time_to_die)
			{
				pthread_mutex_lock(&data->philo[i].m_state);
				data->philo[i].state = DEAD;
				pthread_mutex_unlock(&data->philo[i].m_state);
				protected_print(data->info.write, &data->philo[i]);
			}
			pthread_mutex_unlock(&data->philo[i].lastmeal);
		}
		pthread_mutex_lock(&data->info.die);
		if (data->info.dead)
			break ;
		pthread_mutex_unlock(&data->info.die);
	}
	return (pthread_mutex_unlock(&data->info.die), (void *)0);
}

int	dontstop_believin(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->die);
	//pthread_mutex_lock(&philo->meal);
	if (!philo->info->dead && (philo->info->max_meals == -1
			|| philo->meals < philo->info->max_meals))
	{
		//pthread_mutex_unlock(&philo->meal);
		return (pthread_mutex_unlock(&philo->info->die), 1);
	}
	//pthread_mutex_unlock(&philo->meal);
	return (pthread_mutex_unlock(&philo->info->die), 0);
}

void	uber_fork(t_philo *philo, pthread_mutex_t *fork)
{
	pthread_mutex_lock(fork);
	pthread_mutex_lock(&philo->info->write);
	printf("%llu %d has taken a fork\n",
		get_time() - philo->info->start_time, philo->id + 1);
	pthread_mutex_unlock(&philo->info->write);
}

void	uber_eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
		uber_fork(philo, philo->left);
	else
		uber_fork(philo, philo->right);
	if (philo->id % 2 == 0)
		uber_fork(philo, philo->right);
	else
		uber_fork(philo, philo->left);
	pthread_mutex_lock(&philo->m_state);
	philo->state = EATING;
	pthread_mutex_unlock(&philo->m_state);
	pthread_mutex_lock(&philo->lastmeal);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->lastmeal);
	protected_print(philo->info->write, philo);
	usleep(philo->info->time_to_eat * 1000);
	if (philo->id % 2 == 0)
		pthread_mutex_unlock(philo->left);
	else
		pthread_mutex_unlock(philo->right);
	if (philo->id % 2 == 0)
		pthread_mutex_unlock(philo->right);
	else
		pthread_mutex_unlock(philo->left);
	philo->meals++;
}

void	*set_philo(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (dontstop_believin(philo))
	{
		uber_eat(philo);
		pthread_mutex_lock(&philo->m_state);
		philo->state = SLEEPING;
		pthread_mutex_unlock(&philo->m_state);
		protected_print(philo->info->write, philo);
		usleep(philo->info->time_to_sleep * 1000);
		pthread_mutex_lock(&philo->m_state);
		philo->state = THINKING;
		pthread_mutex_unlock(&philo->m_state);
		protected_print(philo->info->write, philo);
	}
	pthread_mutex_lock(&philo->info->write);
	printf("%d sort\n", philo->id + 1);
	pthread_mutex_unlock(&philo->info->write);
	return ((void *)0);
}
