/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 01:19:50 by zmourtab          #+#    #+#             */
/*   Updated: 2024/07/28 01:45:23 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char *av[])
{
	t_philo	*philos;
	t_data	data;

	data = handleinput(ac, av);
	philos = initphilo(data);
	(void)data;
	(void)philos;
	return (0);
}
