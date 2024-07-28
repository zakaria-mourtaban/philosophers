/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observerroutine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 02:14:56 by zmourtab          #+#    #+#             */
/*   Updated: 2024/07/28 03:12:52 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ateenough(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->data.numberofphilo)
	{
		if (philos[i].timesate != philos->data.timestoeat)
			return (0);
	}
	return (1);
}

int	deadcheck(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->data.numberofphilo)
	{
		if ((get_current_time() - philos[i].lastmeal)
			> (long unsigned int)philos[i].data.timetodie)
		{
			printf("%ld %d has died\n", (get_current_time() - philos[i].startingtime), philos[i].id);
			pthread_mutex_lock(&philos->data.deadmutex);
			philos[i].data.dead = 1;
			pthread_mutex_unlock(&philos->data.deadmutex);
			return (1);
		}
		i++;
	}
	return (0);
}

void	*observerroutine(void *arg)
{
	t_philo *philos;

	philos = arg;
	pthread_mutex_lock(&philos->data.syncmutex);
	philos->data.sync = 1;
	pthread_mutex_unlock(&philos->data.syncmutex);
	while (1)
	{
		if (deadcheck(philos) == 1 || ateenough(philos) == 1)
		{
			pthread_mutex_lock(&philos->data.deadmutex);
			philos->data.dead = 1;
			pthread_mutex_unlock(&philos->data.deadmutex);
			break ;
		}
	}
	return (NULL);
}