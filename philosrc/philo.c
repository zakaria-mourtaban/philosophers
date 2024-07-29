/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 12:29:05 by zmourtab          #+#    #+#             */
/*   Updated: 2024/07/29 18:26:29 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	test_data(const t_data *data)
// {
// 	printf("Time to eat: %d\n", data->timetoeat);
// 	printf("Time to sleep: %d\n", data->timetosleep);
// 	printf("Time to die: %d\n", data->timetodie);
// 	printf("Number of philosophers: %d\n", data->numberofphilo);
// 	printf("Start time: %zu\n", data->starttime);
// 	printf("Is dead: %d\n", data->dead);
// }

// void	check_mutexes(t_data *data)
// {
// 	if (pthread_mutex_trylock(&data->deadmutex) != 0)
// 	{
// 		printf("deadmutex is not locked\n");
// 	}
// 	pthread_mutex_unlock(&data->deadmutex);
// }

void	launchthreads(t_philo *philos)
{
	pthread_t	observer;
	int			i;

	i = 0;
	while (i < philos->data->numberofphilo)
	{
		pthread_create(&philos[i].thread, NULL, philoroutine,
			(void *)&philos[i]);
		i++;
	}
	pthread_create(&observer, NULL, observerroutine, (void *)philos);
	i = 0;
	while (i < philos->data->numberofphilo)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	pthread_join(observer, NULL);
}

void	freeall(t_philo *philos)
{
	int		i;

	i = 0;
	while (i < philos->data->numberofphilo)
	{
		pthread_mutex_destroy(&philos[i].eatingmutex);
		pthread_mutex_destroy(&philos->data->forks[i]);
		i++;
	}
	if (philos->data->deadmutex)
	pthread_mutex_destroy(&philos->data->deadmutex);
	pthread_mutex_destroy(&philos->data->datamutex);
	free(philos->data->forks);
	free(philos->data);
	free(philos);
}

int	main(int ac, char **av)
{
	t_philo *philos;

	philos = NULL;
	initphilos(&philos, ac, av);
	launchthreads(philos);
	freeall(philos);
	return (0);
}