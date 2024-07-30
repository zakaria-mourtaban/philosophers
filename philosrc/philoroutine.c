/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philoroutine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:53:54 by zmourtab          #+#    #+#             */
/*   Updated: 2024/07/30 15:38:08 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	isdeadloop(t_philo *philo)
{
	int	i;

	pthread_mutex_lock(&philo->data->deadmutex);
	i = philo->data->dead;
	pthread_mutex_unlock(&philo->data->deadmutex);
	return (i);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->rightfork);
	if (isdeadloop(philo) == 1)
	{
		pthread_mutex_unlock(philo->rightfork);
		return ;
	}
	printing(philo, "has taken a fork");
	if (philo->data->numberofphilo == 1)
	{
		precise_usleep(philo->data->timetodie + 1);
		pthread_mutex_unlock(philo->rightfork);
		return ;
	}
	pthread_mutex_lock(philo->leftfork);
	printing(philo, "has taken a fork");
	pthread_mutex_lock(&philo->eatingmutex);
	philo->iseating = 1;
	pthread_mutex_unlock(&philo->eatingmutex);
	printing(philo, "is eating");
	philo->mealtime = get_current_time();
	precise_usleep(philo->data->timetoeat);
	pthread_mutex_lock(&philo->eatingmutex);
	philo->iseating = 0;
	pthread_mutex_unlock(&philo->eatingmutex);
	pthread_mutex_unlock(philo->leftfork);
	pthread_mutex_unlock(philo->rightfork);
}

void	thinking(t_philo *philo)
{
	printing(philo, "is thinking");
}

void	sleeping(t_philo *philo)
{
	printing(philo, "is sleeping");
	precise_usleep(philo->data->timetosleep);
}

void	*philoroutine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->id % 2 == 0)
		precise_usleep(1);
	while (isdeadloop(philo) != 1 && philo->timesate != philo->data->timestoeat)
	{
		if (isdeadloop(philo) == 1)
			break ;
		eating(philo);
		pthread_mutex_lock(&philo->data->datamutex);
		philo->timesate += 1;
		pthread_mutex_unlock(&philo->data->datamutex);
		if (isdeadloop(philo) == 1)
			break ;
		thinking(philo);
		if (isdeadloop(philo) == 1)
			break ;
		sleeping(philo);
	}
	pthread_mutex_lock(&philo->data->datamutex);
	philo->data->nbfull += 1;
	pthread_mutex_unlock(&philo->data->datamutex);
	return (NULL);
}
