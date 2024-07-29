/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:14:52 by zmourtab          #+#    #+#             */
/*   Updated: 2024/07/24 19:05:49 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_atoll(const char *str)
{
	long long	result;
	int			sign;
	int			i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
	{
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	result *= sign;
	return (result);
}

int	ft_atoi(const char *c)
{
	int	i;
	int	nb;
	int	neg;

	i = 0;
	nb = 0;
	neg = 1;
	while (c[i] == ' ' || c[i] == '\t' || c[i] == '\v'
		|| c[i] == '\f' || c[i] == '\n' || c[i] == '\r')
		i++;
	if (c[i] == '-')
		neg = -1;
	if (c[i] == '-' || c[i] == '+')
		i++;
	while (c[i] >= 48 && c[i] <= 57 && c[i] != '\0')
	{
		nb *= 10;
		nb += ((int)c[i] - 48);
		i++;
	}
	return (nb * neg);
}
