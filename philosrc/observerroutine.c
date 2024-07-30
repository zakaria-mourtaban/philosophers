/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observerroutine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:47:59 by zmourtab          #+#    #+#             */
/*   Updated: 2024/07/30 15:44:15 by zmourtab         ###   ########.fr       */
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
		pthread_mutex_lock(&philos[i].data->datamutex);
		if ((get_current_time()
				- philos[i].mealtime) >= (philos[i].data->timetodie)
			&& philos[i].iseating != 1)
		{
			printf("%ld %d has died\n", get_current_time()
				- philos->data->starttime, philos[i].id);
			pthread_mutex_lock(&philos->data->deadmutex);
			philos[0].data->dead = 1;
			pthread_mutex_unlock(&philos->data->deadmutex);
			pthread_mutex_unlock(&philos[i].eatingmutex);
			pthread_mutex_unlock(&philos[i].data->datamutex);
			return (1);
		}
		pthread_mutex_unlock(&philos[i].data->datamutex);
		pthread_mutex_unlock(&philos[i].eatingmutex);
		i++;
	}
	return (0);
}

int	checkfull(t_philo *philos)
{
	int	i;
	int	cnt;

	cnt = 0;
	i = 0;
	if (philos->data->timestoeat == -1)
		return (0);
	while (i < philos->data->numberofphilo)
	{
		pthread_mutex_lock(&philos[i].data->datamutex);
		if (philos[i].timesate == philos->data->timestoeat)
			cnt++;
		pthread_mutex_unlock(&philos[i].data->datamutex);
		i++;
	}
	if (cnt == philos->data->numberofphilo)
	{
		pthread_mutex_lock(&philos->data->deadmutex);
		philos[0].data->dead = 1;
		pthread_mutex_unlock(&philos->data->deadmutex);
		return (1);
	}
	return (0);
}

void	*observerroutine(void *args)
{
	t_philo	*philos;

	philos = args;
	while (1)
	{
		if (checkfull(philos) == 1)
			break ;
		if (isdeadcheck(philos) == 1)
			break ;
	}
	return (NULL);
}
