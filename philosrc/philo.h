/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 00:14:44 by zmourtab          #+#    #+#             */
/*   Updated: 2024/07/30 17:11:21 by zmourtab         ###   ########.fr       */
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

typedef struct s_philo	t_philo;

typedef struct s_data
{
	int					timetoeat;
	int					timetosleep;
	long unsigned int	timetodie;
	int					numberofphilo;
	int					timestoeat;
	int					nbfull;
	size_t				starttime;
	int					dead;
	pthread_mutex_t		deadmutex;
	pthread_mutex_t		*forks;
	pthread_mutex_t		datamutex;
	t_philo				*philos;
}						t_data;

typedef struct s_philo
{
	int					rightforkid;
	int					leftforkid;
	pthread_t			thread;
	int					id;
	unsigned long		last_meal;
	unsigned long		mealtime;
	int					timesate;
	int					iseating;
	pthread_mutex_t		eatingmutex;
	pthread_mutex_t		*leftfork;
	pthread_mutex_t		*rightfork;
	t_data				*data;
}						t_philo;
void					printing(t_philo *philo, char *msg);
t_data					handleinput(int ac, char **av);
void					initphilos(t_philo **philos, int ac, char **av);
unsigned long			get_current_time(void);
void					precise_usleep(unsigned int microseconds);
void					*observerroutine(void *args);
void					*philoroutine(void *arg);
void					unlockmut(t_philo *philo);
#endif
