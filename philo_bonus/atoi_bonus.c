/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 21:33:40 by het-tale          #+#    #+#             */
/*   Updated: 2022/09/20 13:57:03 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	is_digit(const char	*str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static	int	ft_isspace(const char *str, int i)
{
	while (str[i] == ' ' || str[i] == '\f' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\r' || str[i] == '\v')
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	int				i;
	unsigned long	res;
	int				d;

	i = 0;
	res = 0;
	d = 0;
	i = ft_isspace(str, i);
	if (str[i] == '+')
		i++;
	if (is_digit(str + i) == 1)
	{
		while (str[i] >= 48 && str[i] <= 57)
		{
			res = res * 10 + (str[i] - 48);
			i++;
		}
	}
	else
		d = -1;
	if (res > MAX_INT)
		d = -1;
	if (d == -1)
		return (d);
	return (res);
}
