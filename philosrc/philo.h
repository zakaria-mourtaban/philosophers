/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 17:43:24 by zmourtab          #+#    #+#             */
/*   Updated: 2024/07/26 01:49:14 by zmourtab         ###   ########.fr       */
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

typedef struct s_philoconf
{
	unsigned int	numberofphil;
	unsigned int	timetoeat;
	unsigned int	timetosleep;
	unsigned int	timetodie;
	unsigned int	timestoeat;
}					t_philoconf;

typedef struct s_philot
{
	pthread_mutex_t	leftforkmutex;
	pthread_mutex_t	rightforkmutex;
	pthread_mutex_t	timesatemutex;
	size_t			startofsim;
	size_t			timelastmeal;
	int				*lfork;
	int				*rfork;
	int				timestoeat;
	int				timesate;
	int				id;
}					t_philot;

typedef struct s_philopointer
{
	int				timestoeat;
	pthread_mutex_t *deadmutex;
	pthread_mutex_t *timestoeatmutex;
	pthread_mutex_t	*mutexs;
	pthread_t		*threadid;
	int				*forks;
	int				*dead;
}					t_philopointer;

#endif