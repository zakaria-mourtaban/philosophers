/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 17:43:24 by zmourtab          #+#    #+#             */
/*   Updated: 2024/07/28 02:59:48 by zmourtab         ###   ########.fr       */
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

typedef struct s_data
{
	int				timetoeat;
	int				timetosleep;
	int				timetodie;
	int				timestoeat;
	int				numberofphilo;
	int				starttime;
	int				sync;
	int				dead;
	pthread_mutex_t	deadmutex;
	pthread_mutex_t	syncmutex;
	pthread_mutex_t	*forks;
}					t_data;

typedef struct s_philo
{
	pthread_mutex_t	firstfork;
	pthread_mutex_t	secondfork;
	pthread_mutex_t	iseatingmutex;
	pthread_t		threadid;
	int				id;
	unsigned long	startingtime;
	unsigned long	lastmeal;
	int				iseating;
	int				timesate;
	t_data			data;
}					t_philo;

t_philo				*initphilo(t_data data);
t_data				handleinput(int ac, char **av);
size_t				get_current_time(void);
void				precise_usleep(unsigned int microseconds);
void				*philoroutine(void *arg);
void				*observerroutine(void *arg);
#endif