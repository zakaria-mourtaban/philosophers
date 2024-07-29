/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observerroutine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:47:59 by zmourtab          #+#    #+#             */
/*   Updated: 2024/07/29 18:39:40 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	isdeadcheck(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->data->numberofphilo)
	{
		pthread_mutex_lock(&philos[i].eatingmutex);
		if ((get_current_time()
				- (philos[i].last_meal)) > (long unsigned int)philos[i].data->timetodie
			&& philos[i].iseating != 1)
		{
			printf("%ld philosopher[%d] has died\n", get_current_time()
				- philos->data->starttime, philos[i].id);
			pthread_mutex_lock(&philos->data->deadmutex);
			philos[0].data->dead = 1;
			pthread_mutex_unlock(&philos->data->deadmutex);
			pthread_mutex_unlock(&philos[i].eatingmutex);
			return (1);
		}
		pthread_mutex_unlock(&philos[i].eatingmutex);
	}
	return (0);
}

int	checkfull(t_philo *philos)
{
	int i;
	pthread_mutex_lock(&philos->data->datamutex);
	i = philos->data->nbfull;
	pthread_mutex_unlock(&philos->data->datamutex);
	if (philos->data->numberofphilo == i)
		return (1);
	return (0);
}

void	*observerroutine(void *args)
{
	t_philo	*philos;

	philos = args;
	while (1)
	{
		if (isdeadcheck(philos) == 1
			|| checkfull(philos) == 1)
			break ;
		usleep(200);
	}
	return (NULL);
}
