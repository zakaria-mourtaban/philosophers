/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo->c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 01:19:50 by zmourtab          #+#    #+#             */
/*   Updated: 2024/07/28 01:56:52 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	launchthreads(t_philo *philos)
{
	pthread_t	observer;
	int			i;

	i = 0;
	while (i < philos->data.numberofphilo)
	{
		pthread_create(&philos[i].threadid, NULL, philoroutine, philos);
		i++;
	}
	pthread_create(&observer, NULL, observerroutine, philos);
	pthread_join(observer, NULL);
}

int	main(int ac, char *av[])
{
	t_philo	*philos;
	t_data	data;

	data = handleinput(ac, av);
	philos = initphilo(data);
	launchthreads(philos);
	return (0);
}
