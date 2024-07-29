/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initphilos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:34:08 by zmourtab          #+#    #+#             */
/*   Updated: 2024/07/29 16:04:06 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	while (i < data->numberofphilo)
	{
		((*philos) + i)->data = data;
		((*philos) + i)->id = i + 1;
		((*philos) + i)->last_meal = get_current_time();
		((*philos) + i)->iseating = 0;
		((*philos) + i)->leftforkid = i;
		((*philos) + i)->rightforkid = (i + 1) % data->numberofphilo;
		if (i % 2 == 1)
		{
		((*philos) + i)->leftforkid = (i - 1) % data->numberofphilo;
		((*philos) + i)->rightforkid = i;
		}
		((*philos) + i)->timesate = 0;
		pthread_mutex_init(&((*philos) + i)->eatingmutex, NULL);
		i++;
	}
}
