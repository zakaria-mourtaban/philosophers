/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 17:48:59 by zmourtab          #+#    #+#             */
/*   Updated: 2024/07/26 02:25:09 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_error(char *msg)
{
	ft_putendl_fd(msg, 1);
	exit(0);
}

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

void	ac5(char **av)
{
	if (!ft_isdigit(*av[1]) || !ft_isdigit(*av[2]) || !ft_isdigit(*av[3])
		|| !ft_isdigit(*av[4]))
		ft_error("all inputs must be digits");
	if (ft_strlen(av[1]) > 12 || ft_strlen(av[2]) > 12 || ft_strlen(av[3]) > 12
		|| ft_strlen(av[4]) > 12)
		ft_error("all inputs must be int");
	if (ft_atoll(av[1]) > (long)INT_MAX || ft_atoll(av[2]) > (long)INT_MAX
		|| ft_atoll(av[3]) > (long)INT_MAX || ft_atoll(av[4]) > (long)INT_MAX)
		ft_error("all inputs must be int");
	if (ft_atoll(av[1]) < (long)INT_MIN || ft_atoll(av[2]) < (long)INT_MIN
		|| ft_atoll(av[3]) < (long)INT_MIN || ft_atoll(av[4]) < (long)INT_MIN)
		ft_error("all inputs must be int");
}

void	ac6(char **av)
{
	if (!ft_isdigit(*av[1]) || !ft_isdigit(*av[2]) || !ft_isdigit(*av[3])
		|| !ft_isdigit(*av[4]) || !ft_isdigit(*av[5]))
		ft_error("all inputs must be digits");
	if (ft_strlen(av[1]) > 12 || ft_strlen(av[2]) > 12 || ft_strlen(av[3]) > 12
		|| ft_strlen(av[4]) > 12 || ft_strlen(av[5]) > 12)
		ft_error("all inputs must be int");
	if (ft_atoll(av[1]) > (long)INT_MAX || ft_atoll(av[2]) > (long)INT_MAX
		|| ft_atoll(av[3]) > (long)INT_MAX || ft_atoll(av[4]) > (long)INT_MAX
		|| ft_atoll(av[5]) > (long)INT_MAX)
		ft_error("all inputs must be int");
	if (ft_atoll(av[1]) < (long)INT_MIN || ft_atoll(av[2]) < (long)INT_MIN
		|| ft_atoll(av[3]) < (long)INT_MIN || ft_atoll(av[4]) < (long)INT_MIN
		|| ft_atoll(av[5]) < (long)INT_MIN)
		ft_error("all inputs must be int");
	if (ft_atoll(av[1]) < 0 || ft_atoll(av[2]) < 0 || ft_atoll(av[3]) < 0
		|| ft_atoll(av[4]) < 0 || ft_atoll(av[5]) < 0)
		ft_error("nums must be bigger than 0");
}

t_philoconf	handleinput(int ac, char **av)
{
	t_philoconf	philo;

	if (ac < 5 || ac > 6)
		ft_error("./philo time_to_eat time_to_sleep time_to_die number_of_philosophers");
	if (ac == 5)
		ac5(av);
	if (ac == 6)
		ac6(av);
	philo.timetoeat = ft_atoll(av[1]);
	philo.timetosleep = ft_atoll(av[2]);
	philo.timetodie = ft_atoll(av[3]);
	philo.timestoeat = -1;
	if (ac == 6)
		philo.timestoeat = ft_atoll(av[5]);
	philo.numberofphil = ft_atoll(av[4]);
	if (philo.numberofphil == 0)
		exit(0);
	return (philo);
}

t_philopointer	*alloc(t_philoconf config)
{
	int				*forks;
	int				*timestoeat;
	pthread_mutex_t	*mutexs;
	t_philopointer	*philoptr;

	philoptr = malloc(sizeof(philoptr));
	if (philoptr == NULL)
		return (NULL);
	forks = malloc(sizeof(int) * config.numberofphil);
	if (forks == NULL)
		return (free(philoptr), ft_error("alloc fail"), NULL);
	forks = ft_calloc(config.numberofphil, sizeof(int));
	mutexs = malloc(sizeof(pthread_mutex_t) * config.numberofphil);
	if (mutexs == NULL)
		return (free(philoptr), free(forks), ft_error("alloc fail"), NULL);
	timestoeat = malloc(sizeof(int) * config.numberofphil);
	if (timestoeat == NULL)
		return (free(philoptr), ft_error("alloc fail"), NULL);
	timestoeat = config.timestoeat;
	philoptr->forks = forks;
	philoptr->mutexs = mutexs;
	philoptr->timestoeat = timestoeat;
	philoptr->dead = malloc(sizeof(int));
	philoptr->deadmutex = malloc(sizeof(pthread_mutex_t));
	return (philoptr);
}

void	initmutex(t_philoconf config, t_philopointer *philoptr)
{
	unsigned int	i;

	i = 0;
	while (i < config.numberofphil
		&& pthread_mutex_init(&(philoptr->mutexs[i++]), NULL) != 0)
		ft_error("mutex init error should free");
	pthread_mutex_init(philoptr->deadmutex, NULL);
	pthread_mutex_init(philoptr->timestoeatmutex, NULL);
}

t_philot	**mallocphilot(t_philoconf config)
{
	unsigned int	i;
	t_philot		**philot;

	philot = (t_philot **)malloc(sizeof(t_philot) * config.numberofphil);
	if (philot == NULL)
		return (NULL);
	i = 0;
	while (i < config.numberofphil)
	{
		philot[i] = malloc(sizeof(philot));
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
	unsigned int	i;

	philot = mallocphilot(config);
	i = 0;
	while (i < config.numberofphil)
	{
		philot[i]->leftforkmutex = philoptr->mutexs[(philot[i]->timelastmeal
				- 1) % config.numberofphil];
		philot[i]->rightforkmutex = philoptr->mutexs[(philot[i]->timelastmeal)
			% config.numberofphil];
		philot[i]->lfork = &(philoptr->forks[(philot[i]->timelastmeal - 1)
				% config.numberofphil]);
		philot[i]->rfork = &(philoptr->forks[(philot[i]->timelastmeal)
				% config.numberofphil]);
		philot[i]->startofsim = get_current_time();
		philot[i]->timelastmeal = get_current_time();
		philot[i]->timestoeat = config.timestoeat;
		philot[i]->timesate = 0;
		pthread_mutex_init(&(philot[i]->timesatemutex), NULL);
		i++;
	}
}
int	checktimesate(t_philoconf config, t_philot **philot,
		t_philopointer *philoptr)
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
		pthread_mutex_lock(philoptr->timestoeatmutex);
		if (get_current_time()
			- philot[i]->timelastmeal > philot[i]->timestoeat)
		{
			printf("he died");
			pthread_mutex_lock(philoptr->deadmutex);
			philoptr->dead = 1;
			pthread_mutex_unlock(philoptr->deadmutex);
			return (1);
		}
		pthread_mutex_unlock(philoptr->timestoeatmutex);
	}
	return (0);
}

//!!!!above 2 functions are for observer loop

void	observerroutine(t_philoconf config, t_philot **philot,
		t_philopointer *philoptr)
{
	while (checkdead(config, philot, philoptr) || checktimesate(config, philot,
			philoptr))
		;
	pthread_mutex_lock(philoptr->deadmutex);
	philoptr->dead = 1;
	pthread_mutex_unlock(philoptr->deadmutex);
}
int	deadloop(t_philoconf config, t_philot **philot, t_philopointer *philoptr)
{
	pthread_mutex_lock(philoptr->deadmutex);
	if (philoptr->dead == 1)
		return (pthread_mutex_unlock(philoptr->deadmutex), 0);
	pthread_mutex_unlock(philoptr->deadmutex);
	return (1);
}

void	philoroutine(t_philoconf config, t_philot **philot,
		t_philopointer *philoptr)
{
	pthread_detach(pthread_self());
	while (deadloop != 1)
	{
		eating();
		sleeping();
		thinking();
	}
}

void	initthreads(t_philoconf config, t_philot **philot,
		t_philopointer *philoptr)
{
}

int	main(int ac, char **av)
{
	t_philoconf		config;
	t_philopointer	*philoptr;
	t_philot		**philot;

	philot = NULL;
	config = handleinput(ac, av);
	philoptr = alloc(config);
	initmutex(config, philoptr);
	initphilos(config, philot, philoptr);
	initthreads(config, philot, philoptr);
	return (0);
}
