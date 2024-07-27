/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo->c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 21:01:40 by zmourtab          #+#    #+#             */
/*   Updated: 2024/07/27 21:11:37 by zmourtab         ###   ########.fr       */
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

t_config	*handleinput(int ac, char **av)
{
	t_config	*philo;

	if (ac < 5 || ac > 6)
		ft_error("./exec timetoeat timetosleep timetodie numberofphilosophers");
	if (ac == 5)
		ac5(av);
	if (ac == 6)
		ac6(av);
	philo = malloc(sizeof(t_config));
	philo->timetoeat = ft_atoll(av[1]);
	philo->timetosleep = ft_atoll(av[2]);
	philo->timetodie = ft_atoll(av[3]);
	philo->isdead = 0;
	philo->timestoeat = -1;
	if (ac == 6)
		philo->timestoeat = ft_atoll(av[5]);
	philo->numberofphil = ft_atoll(av[4]);
	if (philo->numberofphil == 0)
		exit(0);
	philo->starttime = get_current_time();
	return (philo);
}

void	alloc(t_args *args)
{
	int	i;
	int	l;

	i = 0;
	l = 0;
	args->config->forkmutexs = malloc(sizeof(pthread_mutex_t)
			* args->config->numberofphil);
	while (i < args->config->numberofphil)
		l += pthread_mutex_init(&args->config->forkmutexs[i++], NULL);
	i = 0;
	while (i < args->config->numberofphil && l != 1)
		pthread_mutex_destroy(&args->config->forkmutexs[i++]);
	pthread_mutex_init(&args->config->isdeadmutex, NULL);
	pthread_mutex_init(&args->config->timestoeatmutex, NULL);
	i = 0;
	args->philot = malloc(sizeof(t_philot) * args->config->numberofphil);
	while (i < args->config->numberofphil)
	{
		pthread_mutex_init(&args->philot[i].iseatingmutex, NULL);
		args->philot[i].leftfork = args->config->forkmutexs[i
			% args->config->numberofphil];
		args->philot[i].rightfork = args->config->forkmutexs[i + 1
			% args->config->numberofphil];
		args->philot[i].iseating = 0;
		args->philot[i].timestoeat = args->config->timestoeat;
		args->philot[i].timelastmeal = get_current_time();
		args->philot[i].threadid = i;
		i++;
	}
}

int	checktimesate(void *args)
{
	int	i;
	int	timesate;

	i = 0;
	if (((t_args *)args)->config->timestoeat == -1)
		return (0);
	while (i < ((t_args *)args)->config->numberofphil)
	{
		timesate += ((t_args *)args)->philot[i].timesate;
		i++;
	}
	if (timesate != ((t_args *)args)->config->timestoeat
		* ((t_args *)args)->config->numberofphil)
		return (1);
	return (0);
}

int	checkdead(void *args)
{
	int	i;

	i = 0;
	while (i < ((t_args *)args)->config->numberofphil)
	{
		pthread_mutex_lock(&((t_args *)args)->config->timestoeatmutex);
		pthread_mutex_lock(&((t_args *)args)->philot[i].iseatingmutex);
		if (get_current_time()
			- ((t_args *)args)->philot[i].timelastmeal > (size_t)((t_args *)args)->config->timestoeat
			&& ((t_args *)args)->philot[i].iseating != 1)
		{
			printf("he died\n");
			pthread_mutex_lock(&((t_args *)args)->config->isdeadmutex);
			((t_args *)args)->config->isdead = 1;
			pthread_mutex_unlock(&((t_args *)args)->config->isdeadmutex);
			pthread_mutex_unlock(&((t_args *)args)->philot[i].iseatingmutex);
			pthread_mutex_unlock(&((t_args *)args)->config->timestoeatmutex);
			return (1);
		}
		pthread_mutex_unlock(&((t_args *)args)->philot[i].iseatingmutex);
		pthread_mutex_unlock(&((t_args *)args)->config->timestoeatmutex);
		i++;
	}
	return (0);
}

void	*observerroutine(void *args)
{
	while (checkdead(args) != 1 && checktimesate(args) != 1)
		;
	pthread_detach(pthread_self());
	return (NULL);
}

int	deadloop(void *args)
{
	pthread_mutex_lock(&((t_args *)args)->config->isdeadmutex);
	if ((((t_args *)args)->config->isdead) == 1)
		return (pthread_mutex_unlock(&((t_args *)args)->config->isdeadmutex),
			1);
	pthread_mutex_unlock(&((t_args *)args)->config->isdeadmutex);
	return (0);
}

void	sleeping(t_config config, t_philot *philot)
{
	printf("%ld %ld is sleeping\n", get_current_time() - config.starttime,
		philot->threadid);
	precise_usleep(config.timetosleep);
	philot->timelastmeal = get_current_time();
}

void	eating(t_config config, t_philot *philot)
{
	pthread_mutex_lock(&philot->rightfork);
	printf("%ld %ld has taken a fork\n", get_current_time() - config.starttime,
		philot->threadid);
	if (config.numberofphil == 1)
	{
		precise_usleep(config.timetodie);
		pthread_mutex_unlock(&philot->rightfork);
		return ;
	}
	pthread_mutex_lock(&philot->leftfork);
	printf("%ld %ld has taken a fork\n", get_current_time() - config.starttime,
		philot->threadid);
	pthread_mutex_lock(&philot->iseatingmutex);
	philot->iseating = 1;
	pthread_mutex_unlock(&philot->iseatingmutex);
	precise_usleep(config.timetoeat);
	philot->timelastmeal = get_current_time();
	pthread_mutex_lock(&philot->iseatingmutex);
	philot->iseating = 0;
	pthread_mutex_unlock(&philot->iseatingmutex);
	pthread_mutex_unlock(&philot->leftfork);
	pthread_mutex_unlock(&philot->rightfork);
}

void	thinking(t_config config, t_philot *philot)
{
	printf("%ld %ld is thinking\n",get_current_time() - config.starttime,
		philot->threadid);
}

void	*philoroutine(void *args)
{
	while (deadloop(args) != 1)
	{
		eating(*(((t_args *)args)->config), ((t_args *)args)->philot);
		thinking(*(((t_args *)args)->config), ((t_args *)args)->philot);
		sleeping(*(((t_args *)args)->config), ((t_args *)args)->philot);
	}
	pthread_detach(pthread_self());
	return (NULL);
}

void	launchthreads(t_args *args)
{
	pthread_t	observer;
	int			i;

	i = 0;
	if (pthread_create(&observer, NULL, observerroutine, args) != 0)
		ft_error("should be destroying all");
	while (i < args->config->numberofphil)
	{
		if (pthread_create((pthread_t *)&args->philot[i], NULL, philoroutine,
				args) != 0)
			ft_error("should be destroying all");
		i++;
	}
}

int	main(int ac, char **av)
{
	t_args		*args;
	t_philot	*philot;
	t_config	*config;

	philot = NULL;
	config = handleinput(ac, av);
	args = malloc(sizeof(t_args));
	args->config = config;
	args->philot = philot;
	alloc(args);
	launchthreads(args);
	(void)philot;
	(void)config;
	return (0);
}
