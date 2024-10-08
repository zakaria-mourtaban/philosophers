/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initphilos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:34:08 by zmourtab          #+#    #+#             */
/*   Updated: 2024/07/30 15:36:23 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	initphilos2(t_data *data, t_philo **philos, int i)
{
	(*(philos) + i)->data = data;
	(*(philos) + i)->id = i + 1;
	(*(philos) + i)->last_meal = get_current_time() - data->timetoeat;
	(*(philos) + i)->mealtime = data->starttime;
	(*(philos) + i)->iseating = 0;
	(*(philos) + i)->leftforkid = i;
	(*(philos) + i)->rightforkid = (i + 1) % data->numberofphilo;
	(*philos)[i].leftfork = &data->forks[i];
	(*philos)[i].rightfork = &data->forks[(i + 1) % data->numberofphilo];
	(*(philos) + i)->timesate = 0;
}

void	initphilos(t_philo **philos, int ac, char **av)
{
	int		i;
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (data == NULL)
		ft_error("bad data malloc");
	*data = handleinput(ac, av);
	i = 0;
	*philos = malloc(sizeof(t_philo) * data->numberofphilo);
	if (philos == NULL)
		ft_error("bad malloc philos");
	data->philos = *philos;
	while (i < data->numberofphilo)
	{
		initphilos2(data, philos, i);
		pthread_mutex_init(&((*philos) + i)->eatingmutex, NULL);
		i++;
	}
}
