/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleinput.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 01:29:07 by zmourtab          #+#    #+#             */
/*   Updated: 2024/07/28 01:46:47 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

t_data	handleinput(int ac, char **av)
{
	t_data	data;
	int		i;

	i = 0;
	if (ac < 5 || ac > 6)
		ft_error("./exec timetoeat timetosleep timetodie numberofphilosophers");
	ac5(av);
	if (ac == 6)
		ac6(av);
	data.timetoeat = ft_atoll(av[1]);
	data.timetosleep = ft_atoll(av[2]);
	data.timetodie = ft_atoll(av[3]);
	data.dead = 0;
	data.timestoeat = -1;
	if (ac == 6)
		data.timestoeat = ft_atoll(av[5]);
	data.numberofphilo = ft_atoll(av[4]);
	if (data.numberofphilo == 0)
		exit(0);
	data.starttime = get_current_time();
	data.forks = malloc(sizeof(pthread_mutex_t) * data.numberofphilo);
	while (i < data.numberofphilo)
	{
		pthread_mutex_init(&data.forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data.deadmutex, NULL);
	return (data);
}
