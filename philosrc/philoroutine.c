/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philoroutine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:53:54 by zmourtab          #+#    #+#             */
/*   Updated: 2024/07/29 21:33:36 by zmourtab         ###   ########.fr       */
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
	pthread_mutex_lock(&philo->data->forks[philo->rightforkid]);
	printf("%ld %d took a fork\n", get_current_time() - philo->data->starttime,
		philo->id);
	if (philo->data->numberofphilo == 1)
	{
		precise_usleep(philo->data->timetodie + 1);
		pthread_mutex_unlock(&philo->data->forks[philo->rightforkid]);
		return ;
	}
	pthread_mutex_lock(&philo->data->forks[philo->leftforkid]);
	printf("%ld %d took a fork\n", get_current_time() - philo->data->starttime,
		philo->id);
	pthread_mutex_lock(&philo->eatingmutex);
	philo->iseating = 1;
	pthread_mutex_unlock(&philo->eatingmutex);
	philo->last_meal = philo->mealtime;
	printf("%ld %d is eating\n", get_current_time() - philo->data->starttime,
		philo->id);
	precise_usleep(philo->data->timetoeat);
	pthread_mutex_lock(&philo->eatingmutex);
	philo->mealtime = get_current_time();
	philo->iseating = 0;
	pthread_mutex_unlock(&philo->eatingmutex);
	pthread_mutex_unlock(&philo->data->forks[philo->rightforkid]);
	pthread_mutex_unlock(&philo->data->forks[philo->leftforkid]);
}

void	thinking(t_philo *philo)
{
	printf("%ld %d is thinking\n", get_current_time() - philo->data->starttime,
		philo->id);
}

void	sleeping(t_philo *philo)
{
	printf("%ld %d is sleeping\n", get_current_time() - philo->data->starttime,
		philo->id);
	precise_usleep(philo->data->timetosleep);
}

void	*philoroutine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->id % 2 == 0)
		precise_usleep(philo->data->timetodie / 2);
	while (isdeadloop(philo) != 1 && philo->timesate != philo->data->timestoeat)
	{
		if (isdeadloop(philo) == 1)
			break ;
		eating(philo);
		if (isdeadloop(philo) == 1)
			break ;
		thinking(philo);
		if (isdeadloop(philo) == 1)
			break ;
		sleeping(philo);
		pthread_mutex_lock(&philo->data->datamutex);
		philo->timesate += 1;
		pthread_mutex_unlock(&philo->data->datamutex);
		precise_usleep(1);
	}
	pthread_mutex_lock(&philo->data->datamutex);
	philo->data->nbfull += 1;
	pthread_mutex_unlock(&philo->data->datamutex);
	return (NULL);
}
