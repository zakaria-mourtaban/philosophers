/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 17:43:24 by zmourtab          #+#    #+#             */
/*   Updated: 2024/07/27 23:19:01 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "../libft/libft.h"
# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philot
{
	pthread_mutex_t	rightfork;
	pthread_mutex_t	leftfork;
	pthread_mutex_t	iseatingmutex;
	unsigned int	timelastmeal;
	int				iseating;
	int				timestoeat;
	int				timesate;
	pthread_t		threadid;
}					t_philot;

typedef struct s_config
{
	pthread_mutex_t	*forkmutexs;
	pthread_mutex_t	isdeadmutex;
	pthread_mutex_t	timestoeatmutex;
	unsigned int	starttime;
	int				isdead;
	int				timetoeat;
	int				timetosleep;
	int				timetodie;
	int				timestoeat;
	int				numberofphil;
}					t_config;

typedef struct s_args
{
	t_config *config;
	t_philot *philot;
}	t_args;

#endif