/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:01:37 by zmourtab          #+#    #+#             */
/*   Updated: 2024/07/30 12:01:53 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	printing(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->data->datamutex);
	printf("%ld %d %s\n", get_current_time() - philo->data->starttime,
		philo->id, msg);
	pthread_mutex_unlock(&philo->data->datamutex);
}
