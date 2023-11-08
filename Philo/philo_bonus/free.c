/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:05:56 by bpleutin          #+#    #+#             */
/*   Updated: 2023/11/08 17:08:48 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	free_all(t_data *data)
{
	sem_close(data->info.write);
	sem_close(data->info.start);
	sem_close(data->info.end);
	sem_close(data->info.die);
	sem_close(data->info.is_done);
	sem_close(data->info.is_dead);
	sem_close(data->info.last);
	sem_close(data->info.s_state);
	sem_close(data->info.meal);
	sem_close(data->info.forks);
	free(data->philo);
}
