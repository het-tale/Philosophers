/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 17:00:37 by het-tale          #+#    #+#             */
/*   Updated: 2022/09/14 21:15:07 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	while (get_time() < awake + time_to)
	{
		if (is_dead(args) || end_simulation(args))
			break ;
		usleep(100);
	}
}

void	is_max_ate(t_args *args)
{
	int	i;

	i = 0;
	while (args->number_of_times != -1 && i < args->philo_number
		&& is_all_ate(&args->philo[i]))
		i++;
	if (i == args->philo_number)
	{
		pthread_mutex_lock(&args->end_mutex);
		args->end_sim = 1;
		pthread_mutex_unlock(&args->end_mutex);
	}
}

void	print_death(t_args *args, int i)
{
	unsigned int	time;

	pthread_mutex_lock(&args->msg_mutex);
	time = get_time() - args->start_time;
	printf("%u %d %s\n", time, args->philo[i].philo_id, "died");
	pthread_mutex_unlock(&args->msg_mutex);
}

void	check_death(t_args *args)
{
	int	i;

	while (end_simulation(args) == 0)
	{
		i = -1;
		while (++i < args->philo_number && is_dead(args) == 0)
		{
			pthread_mutex_lock(&args->lastmeal_mutex);
			if (get_time() - args->philo[i].lastmeal > args->time_to_die)
			{
				pthread_mutex_lock(&args->death_mutex);
				args->died = 1;
				pthread_mutex_unlock(&args->death_mutex);
				print_death(args, i);
			}
			pthread_mutex_unlock(&args->lastmeal_mutex);
			usleep(200);
		}
		if (is_dead(args))
			break ;
		is_max_ate(args);
	}
}
