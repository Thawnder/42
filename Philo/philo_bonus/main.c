/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <bpleutin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:06:13 by bpleutin          #+#    #+#             */
/*   Updated: 2023/10/26 14:52:29 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

void	*init_all(t_data *data, char **argv, int i)
{
	if ((!sem_unlink("forks") && !sem_unlink("write") && !sem_unlink("start")
			&& !sem_unlink("end") && !sem_unlink("die") && !sem_unlink("last")
			&& !sem_unlink("state") && !sem_unlink("meal")
			&& !sem_unlink("is_done") && !sem_unlink("is_dead")) || 1)
		data->info.gang_len = (int) ft_atoll(argv[1]);
	data->info.time_to_die = ft_atoll(argv[2]);
	data->info.time_to_eat = ft_atoll(argv[3]);
	data->info.time_to_sleep = ft_atoll(argv[4]);
	data->info.forks = sem_open("forks", O_CREAT, 0644, data->info.gang_len);
	data->info.write = sem_open("write", O_CREAT | O_EXCL, 0644, 1);
	data->info.start = sem_open("start", O_CREAT | O_EXCL, 0644, 1);
	data->info.end = sem_open("end", O_CREAT | O_EXCL, 0644, 1);
	data->info.die = sem_open("die", O_CREAT | O_EXCL, 0644, 1);
	data->info.is_done = sem_open("is_done", O_CREAT | O_EXCL, 0644, 1);
	data->info.is_dead = sem_open("is_dead", O_CREAT | O_EXCL, 0644, 1);
	data->info.last = sem_open("last", O_CREAT | O_EXCL, 0644, 1);
	data->info.s_state = sem_open("state", O_CREAT | O_EXCL, 0644, 1);
	data->info.meal = sem_open("meal", O_CREAT | O_EXCL, 0644, 1);
	data->philo = ft_calloc(data->info.gang_len, sizeof(t_philo));
	while (++i < data->info.gang_len)
	{
		data->philo[i].info = &data->info;
		data->philo[i].id = i;
	}
	return (data->info.start_time = get_time(), (void *)0);
}

void	free_all(t_data *data)
{
	int	i;

	i = -1;
	sem_post(data->info.start);
	while (++i < data->info.gang_len)
		sem_wait(data->info.is_done);
	sem_close(data->info.forks);
	sem_close(data->info.write);
	sem_close(data->info.start);
	sem_close(data->info.end);
	sem_close(data->info.die);
	sem_close(data->info.is_done);
	sem_close(data->info.is_dead);
	sem_close(data->info.s_state);
	sem_close(data->info.meal);
	sem_close(data->info.last);
	free(data->philo);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	if (argc < 5 || argc > 6 || argv[1][0] == '-' || argv[2][0] == '-'
		|| argv[3][0] == '-' || argv[4][0] == '-')
		return (printf("Invalid args\n"), -1);
	data.info.gang_len = 0;
	data.info.finished = 0;
	data.info.max_meals = -1;
	if (argc == 6)
		data.info.max_meals = (int) ft_atoll(argv[5]);
	i = -1;
	init_all(&data, argv, i);
	while (++i < data.info.gang_len)
		data.philo[i].last_meal = get_time();
	sem_wait(data.info.start);
	sem_wait(data.info.die);
	i = -1;
	while (++i < data.info.gang_len)
	{
		data.philo[i].pid = fork();
		if (data.philo[i].pid == 0)
			set_philo(&data.philo[i]);
	}
	return (free_all(&data), 0);
}
