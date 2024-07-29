/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philoroutine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:53:54 by zmourtab          #+#    #+#             */
/*   Updated: 2024/07/29 18:19:24 by zmourtab         ###   ########.fr       */
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
	printf("%ld philosopher[%d] took a fork\n", get_current_time()
		- philo->data->starttime, philo->id);
	if (philo->data->numberofphilo == 1)
	{
		precise_usleep(philo->data->timetodie + 1);
		pthread_mutex_unlock(&philo->data->forks[philo->rightforkid]);
		return ;
	}
	pthread_mutex_lock(&philo->data->forks[philo->leftforkid]);
	printf("%ld philosopher[%d] took a fork\n", get_current_time()
		- philo->data->starttime, philo->id);
	pthread_mutex_lock(&philo->eatingmutex);
	philo->iseating = 1;
	pthread_mutex_unlock(&philo->eatingmutex);
	printf("%ld philosopher[%d] is eating\n", get_current_time()
		- philo->data->starttime, philo->id);
	precise_usleep(philo->data->timetoeat);
	philo->last_meal = get_current_time();
	pthread_mutex_lock(&philo->eatingmutex);
	philo->iseating = 0;
	pthread_mutex_unlock(&philo->eatingmutex);
	pthread_mutex_unlock(&philo->data->forks[philo->rightforkid]);
	pthread_mutex_unlock(&philo->data->forks[philo->leftforkid]);
}

void	thinking(t_philo *philo)
{
	printf("%ld philosopher[%d] is thinking\n", get_current_time()
		- philo->data->starttime, philo->id);
}

void	sleeping(t_philo *philo)
{
	printf("%ld philosopher[%d] is sleeping\n", get_current_time()
		- philo->data->starttime, philo->id);
	precise_usleep(philo->data->timetosleep);
	precise_usleep(1000);
}

void	*philoroutine(void *arg)
{
	t_philo	*philo;

	philo = arg;
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
		philo->timesate += 1;
	}
	philo->data->nbfull += 1;
	return (NULL);
}
