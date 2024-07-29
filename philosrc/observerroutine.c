/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observerroutine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:47:59 by zmourtab          #+#    #+#             */
/*   Updated: 2024/07/29 18:17:40 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	isdeadcheck(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->data->numberofphilo)
	{
		if ((get_current_time()
				- (philos[i].last_meal)) > (long unsigned int)philos[i].data->timetodie
			&& philos[i].iseating != 1)
		{
			printf("%ld philosopher[%d] has died\n", get_current_time()
				- philos->data->starttime, philos[i].id);
			pthread_mutex_lock(&philos->data->deadmutex);
			philos[0].data->dead = 1;
			pthread_mutex_unlock(&philos->data->deadmutex);
			return (1);
		}
	}
	return (0);
}
void	*observerroutine(void *args)
{
	t_philo	*philos;

	philos = args;
	while (1)
	{
		if (isdeadcheck(philos) == 1
			|| philos->data->nbfull == philos->data->numberofphilo)
			break ;
		usleep(200);
	}
	return (NULL);
}
