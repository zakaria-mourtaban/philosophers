/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 17:43:24 by zmourtab          #+#    #+#             */
/*   Updated: 2024/07/24 19:24:38 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "../libft/libft.h"
# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
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
	int				*lfork;
	int				*rfork;
}					t_philot;

#endif