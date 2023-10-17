/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:06:13 by bpleutin          #+#    #+#             */
/*   Updated: 2023/10/17 18:11:17 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_alltime	ft_atoll(char *nptr)
{
	int			i;
	int			sign;
	t_alltime	res;

	i = 0;
	sign = 1;
	res = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = res * 10 + nptr[i] - 48;
		i++;
	}
	return ((int)res * sign);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	res;
	size_t	i;

	res = nmemb * size;
	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (res / size != nmemb || res / nmemb != size)
		return (NULL);
	ptr = malloc(res);
	i = 0;
	if (ptr)
	{
		while (i < res)
		{
			*(unsigned char *)(ptr + i) = 0;
			i++;
		}
	}
	return (ptr);
}

void	init_all(t_data *data, int i)
{
	i = -1;
	pthread_mutex_init(&data->write, NULL);
	data->philo = ft_calloc(data->info.gang_size, sizeof(t_philo));
	while (++i < data->info.gang_size)
	{
		data->philo[i].info = &data->info;
		data->philo[i].id = i;
		data->philo[i].last_meal = get_time();
		pthread_mutex_init(&data->philo[i].info->forks[i], NULL);
	}
	i = -1;
	while (++i < data->info.gang_size)
	{
		if (i == 0)
			data->philo[i].left = &data->info.forks[data->info.gang_size];
		else
			data->philo[i].left = &data->info.forks[i - 1];
		if (i == data->info.gang_size - 1)
			data->philo[i].right = &data->info.forks[0];
		else
			data->philo[i].right = &data->info.forks[i];
	}
}

void	free_all(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->info.gang_size)
		pthread_mutex_destroy(&data->philo[i].info->forks[i]);
	pthread_mutex_destroy(&data->write);
	free(data->philo);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	if (argc < 5 || argc > 6)
	{
		printf("Invalid number of args\n");
		return (-1);
	}
	data.info.gang_size = (int) ft_atoll(argv[1]);
	data.info.time_to_die = ft_atoll(argv[2]);
	data.info.time_to_eat = ft_atoll(argv[3]);
	data.info.time_to_sleep = ft_atoll(argv[4]);
	data.info.nbr_of_meals = -1;
	if (argc == 6)
		data.info.nbr_of_meals = (int) ft_atoll(argv[5]);
	i = -1;
	init_all(&data, i);
	pthread_create(&data->timer_tid, NULL, &timer, &data);
	data.info.start_time = get_time();
	while (++i < data->info.gang_size)
		pthread_create(&data->philo[i].tid, NULL, &set_philo, &data->philo[i]);
	pthread_join(&data->timer_tid, NULL);
	free_all(&data);
	return (0);
}
