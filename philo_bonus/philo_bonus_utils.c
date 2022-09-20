/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 17:00:37 by het-tale          #+#    #+#             */
/*   Updated: 2022/09/20 13:56:49 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

unsigned int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	sleep_philo(unsigned int time_to, t_args *args)
{
	unsigned int	awake;

	awake = get_time();
	(void)args;
	while (get_time() < awake + time_to)
	{
		// if (is_dead(args) || end_simulation(args))
		// 	break ;
		usleep(100);
	}
}

