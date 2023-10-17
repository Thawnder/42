/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:50:07 by bpleutin          #+#    #+#             */
/*   Updated: 2023/10/17 17:59:22 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_alltime	get_time(void)
{
	struct timeval	t;
	int	res;

	res = gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

void	timer(void *ptr)
{
	t_data *data;
	int	i;

	data = (t_data *)ptr;
	while (1)
	{
		i = -1;
		while (++i < data->info.gang_size)
		{
			if (get_time() - data->philo[i].last_meal
				>= data->info.time_to_die)
					/* c'est ciao */
		}		
	}
}

void	uber_eat()
{

}

void	uber_sleep()
{

}

void	uber_think()
{

}

void	philosopher(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (1)
	{

	}
}
