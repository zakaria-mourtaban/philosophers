/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 17:48:59 by zmourtab          #+#    #+#             */
/*   Updated: 2024/07/24 18:29:32 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_error(char *msg)
{
	ft_putendl_fd(msg, 1);
	exit(0);
}

void	precise_usleep(unsigned int microseconds)
{
	unsigned int	elapsed_time;
	unsigned int	remaining_time;
	struct timeval	start_time;
	struct timeval	current_time;

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

void	ac5(int ac, char **av)
{
	if (!ft_isdigit(av[1]) || !ft_isdigit(av[2]) || !ft_isdigit(av[3])
		|| !ft_isdigit(av[4]))
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

void	ac6(int ac, char **av)
{
	if (!ft_isdigit(av[1]) || !ft_isdigit(av[2]) || !ft_isdigit(av[3])
		|| !ft_isdigit(av[4]) || !ft_isdigit(av[5]))
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

t_philo	handleinput(int ac, char **av)
{
	t_philo	philo;

	if (ac < 5 || ac > 6)
		ft_error("./philo time_to_eat time_to_sleep time_to_die number_of_philosophers");
	if (ac == 5)
		ac5(ac, av);
	if (ac == 6)
		ac6(ac, av);
	philo.timetoeat = ft_atoll(av[1]);
	philo.timetosleep = ft_atoll(av[2]);
	philo.timetodie = ft_atoll(av[3]);
	philo.timestoeat = 0;
	if (ac == 6)
		philo.timestoeat = ft_atoll(av[5]);
	philo.numberofphil = ft_atoll(av[4]);
	return (philo);
}

int	main(int ac, char **av)
{
	t_philo	config;

	config = handleinput(ac, av);
	return (0);
}
