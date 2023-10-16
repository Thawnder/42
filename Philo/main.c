/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:06:13 by bpleutin          #+#    #+#             */
/*   Updated: 2023/10/16 15:44:10 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

alltime	ft_atoll(char *nptr)
{
	int				i;
	int				sign;
	alltime			res;

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

void	init_all(t_data *data, int argc, char **argv)
{
	data->gang_size = (int) ft_atoll(argv[1]);
	data->time_to_die = ft_atoll(argv[2]);
	data->time_to_eat = ft_atoll(argv[3]);
	data->time_to_sleep = ft_atoll(argv[4]);
	if (argc == 6)
		data->nbr_of_meals = (int) ft_atoll(argv[5]);
	data->philo = ft_calloc(data->gang_size, sizeof(t_philo));
}

void	free_all(t_data *data)
{
	int	i;

	i = 0;
	while (data->philo[i])
		free(data->philo[i++]);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
	{
		printf("Invalid number of args\n");
		return (-1);
	}
	init_all(&data, argc, argv);
	free_all(&data);
	return (0);
}

