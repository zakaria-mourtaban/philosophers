/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initphilos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 01:44:27 by zmourtab          #+#    #+#             */
/*   Updated: 2024/07/28 02:11:04 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*initphilo(t_data data)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = malloc(sizeof(t_philo) * data.numberofphilo);
	if (philo == NULL)
		exit(77);
	while (i < data.numberofphilo)
	{
		philo[i].data = data;
		philo[i].firstfork = data.forks[i];
		philo[i].secondfork = data.forks[(i + 1) % data.numberofphilo];
		philo[i].id = i + 1;
		philo[i].timesate = 0;
		philo[i].data.sync = 0;
		pthread_mutex_init(&philo[i].iseatingmutex,NULL);
		pthread_mutex_init(&philo[i].data.syncmutex,NULL);
		i++;
	}
	return philo;
}