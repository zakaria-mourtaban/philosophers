/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philoroutine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 02:01:05 by zmourtab          #+#    #+#             */
/*   Updated: 2024/07/28 03:17:22 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thinking(t_philo *philo)
{
	printf("%ld %d is thinking\n", get_current_time() - philo->startingtime,
		philo->id);
}

void	sleeping(t_philo *philo)
{
	printf("%ld %d is sleeping\n", get_current_time() - philo->startingtime,
		philo->id);
	precise_usleep(philo->data.timetosleep);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->firstfork);
	if (philo->data.numberofphilo == 1)
	{
		precise_usleep(philo->data.timetodie);
		pthread_mutex_unlock(&philo->firstfork);
		return ;
	}
	printf("%ld %d took a fork\n", get_current_time() - philo->startingtime,
		philo->id);
	pthread_mutex_lock(&philo->secondfork);
	printf("%ld %d took a fork\n", get_current_time() - philo->startingtime,
		philo->id);
	pthread_mutex_lock(&philo->iseatingmutex);
	philo->iseating = 1;
	pthread_mutex_unlock(&philo->iseatingmutex);
	printf("%ld %d is eating\n", get_current_time() - philo->startingtime,
		philo->id);
	precise_usleep(philo->data.timetoeat);
	philo->timesate += 1;
	pthread_mutex_unlock(&philo->firstfork);
	pthread_mutex_unlock(&philo->secondfork);
}

int	syncc(t_philo *philo)
{
	pthread_mutex_lock(&philo->data.syncmutex);
	if (philo->data.sync == 0)
		return (pthread_mutex_unlock(&philo->data.syncmutex), 0);
	pthread_mutex_unlock(&philo->data.syncmutex);
	return (1);
}

int		deadloop(t_philo philo)
{
	pthread_mutex_lock(&philo.data.deadmutex);
	if (philo.data.dead == 1)
		return (pthread_mutex_unlock(&philo.data.deadmutex), 1);
	pthread_mutex_unlock(&philo.data.deadmutex);
	return (0);
}

void	*philoroutine(void *arg)
{
	t_philo *philo;

	philo = arg;
	while (syncc(philo) != 1)
		;
	philo->startingtime = get_current_time();
	while (deadloop(philo[0]) != 1)
	{
		if (philo->timesate == philo->data.timestoeat)
			break ;
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	pthread_detach(pthread_self());
	return (NULL);
}