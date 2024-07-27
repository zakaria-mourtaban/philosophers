/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oldcode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 17:48:59 by zmourtab          #+#    #+#             */
/*   Updated: 2024/07/27 21:33:49 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	precise_usleep(unsigned int microseconds)
{
	unsigned int	elapsed_time;
	unsigned int	remaining_time;
	struct timeval	start_time;
	struct timeval	current_time;

	if (microseconds == 0)
		return ;
	remaining_time = microseconds;
	gettimeofday(&start_time, NULL);
	while (remaining_time > 0)
	{
		usleep(remaining_time);
		gettimeofday(&current_time, NULL);
		elapsed_time = (current_time.tv_sec - start_time.tv_sec) * 1000000
			+ (current_time.tv_usec - start_time.tv_usec);
		if (elapsed_time < microseconds)
			remaining_time = microseconds - elapsed_time;
		else
			remaining_time = 0;
	}
}

t_philot	**mallocphilot(t_philoconf config)
{
	int			i;
	t_philot	**philot;

	philot = (t_philot **)malloc(sizeof(t_philot *) * config.numberofphil);
	if (philot == NULL)
		return (NULL);
	i = 0;
	while (i < config.numberofphil)
	{
		philot[i] = malloc(sizeof(t_philot));
		if (philot[i] == NULL)
		{
			ft_error("free everythang");
			return (NULL);
		}
		philot[i]->id = i;
		i++;
	}
	return (philot);
}

void	initphilos(t_philoconf config, t_philot **philot,
		t_philopointer *philoptr)
{
	int	i;
	int	ri;
	int	li;

	philot = mallocphilot(config);
	i = 0;
	while (i < config.numberofphil)
	{
		ri = (philot[i]->id) % config.numberofphil;
		li = (philot[i]->id - 1) % config.numberofphil;
		philot[i]->leftforkmutex = philoptr->mutexs[ri];
		philot[i]->rightforkmutex = philoptr->mutexs[li];
		philot[i]->startofsim = get_current_time();
		philot[i]->timelastmeal = get_current_time();
		philot[i]->timestoeat = config.timestoeat;
		philot[i]->timesate = 0;
		philot[i]->iseating = 1;
		pthread_mutex_init(&(philot[i]->timesatemutex), NULL);
		pthread_mutex_init(&(philot[i]->iseatingmutex), NULL);
		i++;
	}
	pthread_mutex_init(&philoptr->timestoeatmutex, NULL);
}
int	checktimesate(t_philoconf config, t_philot **philot)
{
	int	i;
	int	timesate;

	if (config.timestoeat == -1)
		return (0);
	timesate = 0;
	i = 0;
	while (config.timestoeat != -1 && i > config.numberofphil)
	{
		pthread_mutex_lock(&philot[i]->timesatemutex);
		timesate += philot[i]->timesate;
		i++;
		pthread_mutex_unlock(&philot[i]->timesatemutex);
	}
	if (timesate == config.numberofphil * config.timestoeat)
		return (1);
	return (0);
}

int	checkdead(t_philoconf config, t_philot **philot, t_philopointer *philoptr)
{
	int	i;

	i = 0;
	while (i < config.numberofphil)
	{
		pthread_mutex_lock(&philoptr->timestoeatmutex);
		pthread_mutex_lock(&philot[i]->iseatingmutex);
		if (get_current_time()
			- philot[i]->timelastmeal > (size_t)philot[i]->timestoeat
			&& philot[i]->iseating != 1)
		{
			printf("he died");
			pthread_mutex_lock(philoptr->deadmutex);
			*(philoptr->dead) = 1;
			pthread_mutex_unlock(philoptr->deadmutex);
			pthread_mutex_unlock(&philot[i]->iseatingmutex);
			pthread_mutex_unlock(&philoptr->timestoeatmutex);
			return (1);
		}
		pthread_mutex_unlock(&philot[i]->iseatingmutex);
		pthread_mutex_unlock(&philoptr->timestoeatmutex);
		i++;
	}
	return (0);
}

//!!!!above 2 functions are for observer loop

void	*observerroutine(void *arg)
{
	t_bigphilo		*bigphilo;
	t_philoconf		config;
	t_philot		**philot;
	t_philopointer	*philoptr;

	bigphilo = arg;
	config = bigphilo->config;
	philot = bigphilo->philot;
	philoptr = bigphilo->philotptr;
	pthread_detach(pthread_self());
	while (checkdead(config, philot, philoptr) || checktimesate(config, philot))
		;
	return (NULL);
}
int	deadloop(t_philopointer *philoptr)
{
	pthread_mutex_lock(philoptr->deadmutex);
	if (*(philoptr->dead) == 1)
		return (pthread_mutex_unlock(philoptr->deadmutex), 0);
	pthread_mutex_unlock(philoptr->deadmutex);
	return (1);
}

void	sleeping(t_philoconf config, t_philot *philot)
{
	printf("%ld %d is sleeping", philot->startofsim - get_current_time(),
		philot->id);
	precise_usleep(config.timetosleep);
	philot->timelastmeal = get_current_time();
}

void	eating(t_philoconf config, t_philot *philot)
{
	pthread_mutex_lock(&philot->rightforkmutex);
	printf("%ld %d has taken a fork", philot->startofsim - get_current_time(),
		philot->id);
	if (config.numberofphil == 1)
	{
		precise_usleep(config.timetodie);
		pthread_mutex_unlock(&philot->rightforkmutex);
		return ;
	}
	pthread_mutex_lock(&philot->leftforkmutex);
	printf("%ld %d has taken a fork", philot->startofsim - get_current_time(),
		philot->id);
	pthread_mutex_lock(&philot->iseatingmutex);
	philot->iseating = 1;
	pthread_mutex_unlock(&philot->iseatingmutex);
	precise_usleep(config.timetoeat);
	philot->timelastmeal = get_current_time();
	pthread_mutex_lock(&philot->iseatingmutex);
	philot->iseating = 0;
	pthread_mutex_unlock(&philot->iseatingmutex);
	pthread_mutex_unlock(&philot->leftforkmutex);
	pthread_mutex_unlock(&philot->rightforkmutex);
}

void	thinking(t_philot *philot)
{
	printf("%ld %d is thinking", philot->startofsim - get_current_time(),
		philot->id);
}

void	*philoroutine(void *arg)
{
	t_smallphilo	*smallphilo;
	t_philoconf		config;
	t_philot		*philot;
	t_philopointer	*philoptr;

	smallphilo = arg;
	config = smallphilo->config;
	philot = smallphilo->philot;
	philoptr = smallphilo->philotptr;
	pthread_detach(pthread_self());
	while (deadloop(philoptr) != 1)
	{
		eating(config, philot);
		thinking(philot);
		sleeping(config, philot);
	}
	return (NULL);
}

void	initthreads(t_philoconf config, t_philot **philot,
		t_philopointer *philoptr)
{
	t_bigphilo		bigphilo;
	pthread_t		observer;
	t_smallphilo	smallphilo;
	int				i;

	bigphilo.config = config;
	bigphilo.philot = philot;
	bigphilo.philotptr = philoptr;
	if (pthread_create(&observer, NULL, observerroutine,
			(void *)&bigphilo) != 0)
	{
	}
	ft_error("error creating thread destroy all");
	i = 0;
	while (i < config.numberofphil)
	{
		smallphilo.config = config;
		smallphilo.philot = philot[i];
		smallphilo.philotptr = philoptr;
		pthread_create(&(philoptr->threadid[i]), NULL, philoroutine,
			(void *)&smallphilo);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_philoconf		config;
	t_philopointer	*philoptr;
	t_philot		**philot;

	philot = NULL;
	config = handleinput(ac, av);
	philoptr = alloc(config);
	if (philoptr == NULL)
		ft_error("alloc fail");
	initmutex(config, philoptr);
	initphilos(config, philot, philoptr);
	initthreads(config, philot, philoptr);
	return (0);
}
