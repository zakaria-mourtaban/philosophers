/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timeutils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 01:30:08 by zmourtab          #+#    #+#             */
/*   Updated: 2024/07/29 21:28:16 by zmourtab         ###   ########.fr       */
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

void	precise_usleep(unsigned int milliseconds)
{
	struct timeval	start_time;
	struct timeval	current_time;
	unsigned int	elapsed_time;
	unsigned int	remaining_time;

	if (milliseconds == 0)
		return ;
	remaining_time = milliseconds * 1000;
	gettimeofday(&start_time, NULL);
	while (remaining_time > 0)
	{
		usleep(remaining_time);
		gettimeofday(&current_time, NULL);
		elapsed_time = (current_time.tv_sec - start_time.tv_sec) * 1000000
			+ (current_time.tv_usec - start_time.tv_usec);
		if (elapsed_time < remaining_time)
			remaining_time -= elapsed_time;
		else
			remaining_time = 0;
	}
}
