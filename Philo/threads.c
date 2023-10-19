/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <bpleutin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:50:07 by bpleutin          #+#    #+#             */
/*   Updated: 2023/10/19 18:11:42 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	dontstop_believin(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->die);
	if (!philo->info->dead && (philo->info->max_meals == -1
			|| philo->meals < philo->info->max_meals))
		return (pthread_mutex_unlock(&philo->info->die), 1);
	if (!philo->info->dead && !(philo->info->max_meals == -1
			&& philo->meals < philo->info->max_meals))
		philo->info->finished += 1;
	return (pthread_mutex_unlock(&philo->info->die), 0);
}

void	*timer(void *ptr)
{
	t_data	*data;
	int		i;

	data = (t_data *)ptr;
	while (data->info.finished < data->info.gang_size)
	{
		i = -1;
		while (++i < data->info.gang_size)
		{
			pthread_mutex_lock(&data->philo[i].lastmeal);
			if (dontstop_believin(&data->philo[i])
				&& get_time() - data->philo[i].last_meal
				>= data->info.time_to_die)
			{
				pthread_mutex_lock(&data->philo[i].m_state);
				data->philo[i].state = DEAD;
				pthread_mutex_unlock(&data->philo[i].m_state);
				protected_print(&data->philo[i]);
				return (pthread_mutex_unlock(&data->philo[i].lastmeal),
					(void *)0);
			}
			pthread_mutex_unlock(&data->philo[i].lastmeal);
		}
	}
	return ((void *)0);
}

void	uber_fork(t_philo *philo, pthread_mutex_t *one, pthread_mutex_t *two)
{
	pthread_mutex_lock(one);
	if (!dontstop_believin(philo))
		return ;
	pthread_mutex_lock(&philo->info->write);
	printf("%llu %d has taken a fork\n",
		get_time() - philo->info->start_time, philo->id + 1);
	pthread_mutex_unlock(&philo->info->write);
	pthread_mutex_lock(two);
	if (!dontstop_believin(philo))
		return ;
	pthread_mutex_lock(&philo->info->write);
	printf("%llu %d has taken a fork\n",
		get_time() - philo->info->start_time, philo->id + 1);
	pthread_mutex_unlock(&philo->info->write);
}

void	uber_eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
		uber_fork(philo, philo->left, philo->right);
	else
		uber_fork(philo, philo->right, philo->left);
	if (!dontstop_believin(philo))
		return ;
	pthread_mutex_lock(&philo->m_state);
	philo->state = EATING;
	pthread_mutex_unlock(&philo->m_state);
	if (!dontstop_believin(philo))
		return ;
	pthread_mutex_lock(&philo->lastmeal);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->lastmeal);
	protected_print(philo);
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
		if (!dontstop_believin(philo))
			break ;
		pthread_mutex_lock(&philo->m_state);
		philo->state = SLEEPING;
		pthread_mutex_unlock(&philo->m_state);
		protected_print(philo);
		usleep(philo->info->time_to_sleep * 1000);
		if (!dontstop_believin(philo))
			break ;
		pthread_mutex_lock(&philo->m_state);
		philo->state = THINKING;
		pthread_mutex_unlock(&philo->m_state);
		protected_print(philo);
	}
	pthread_mutex_lock(&philo->info->write);
	printf("%d sort\n", philo->id + 1);
	pthread_mutex_unlock(&philo->info->write);
	return ((void *)0);
}
