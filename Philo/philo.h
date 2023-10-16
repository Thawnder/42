#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef unsigned long long int alltime;

typedef struct s_philo
{
	int		id;
	pthread_t	tid;
	alltime		countdown;
	int		state;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
}		t_philo;

typedef struct s_data
{
	int	gang_size;
	int	nbr_of_meals;
	alltime	time_to_die;
	alltime	time_to_eat;
	alltime	time_to_sleep;
	t_philo	*philo;

}		t_data;

#endif
