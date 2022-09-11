/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 19:29:15 by het-tale          #+#    #+#             */
/*   Updated: 2022/09/11 15:38:24 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
◦ timestamp_in_ms X has taken a fork
◦ timestamp_in_ms X is eating
◦ timestamp_in_ms X is sleeping
◦ timestamp_in_ms X is thinking
◦ timestamp_in_ms X died
**/
time_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	philo_sleep(t_args args, int time_to)
{
	time_t	awake;

	(void)args;
	awake = get_time() + time_to;
	while (get_time() < awake)
	{
		// if (args.end_sim == 1)
		//     break ;
		usleep(100);
	}
}

void	print_msg(t_args args, char *str, time_t time)
{
	pthread_mutex_lock(&args.msg_mutex);
	if (strcmp(str, "fork") == 0)
		printf("%ld %d has taken a fork\n", time, args.philo[args.id].philo_id);
	else if (strcmp(str, "eat") == 0)
		printf("%ld %d is eating\n", time, args.philo[args.id].philo_id);
	else if (strcmp(str, "sleep") == 0)
		printf("%ld %d is sleeping\n", time, args.philo[args.id].philo_id);
	else if (strcmp(str, "think") == 0)
		printf("%ld %d is thinking\n", time, args.philo[args.id].philo_id);
	else if (strcmp(str, "die") == 0)
		printf("%ld %d died\n", time, args.philo[args.id].philo_id);
	pthread_mutex_unlock(&args.msg_mutex);
}

void	eat_routine(t_args args)
{
	time_t	time;

	time = get_time();
	pthread_mutex_lock(&args.forks_mutex[args.philo[args.id].left_i]);
	print_msg(args, "fork", time);
	pthread_mutex_lock(&args.forks_mutex[args.philo[args.id].right_i]);
	print_msg(args, "fork", time);
	print_msg(args, "eat", time);
	pthread_mutex_lock(&args.philo[args.id].lastmeal_mutex);
	args.philo[args.id].lastmeal = get_time();
	pthread_mutex_unlock(&args.philo[args.id].lastmeal_mutex);
	philo_sleep(args, args.time_to_eat);
	pthread_mutex_unlock(&args.forks_mutex[args.philo[args.id].right_i]);
	pthread_mutex_unlock(&args.forks_mutex[args.philo[args.id].left_i]);
}

void	sleep_routine(t_args args)
{
	time_t	time;

	time = get_time();
	print_msg(args, "sleep", time);
	philo_sleep(args, args.time_to_sleep);
}

void	*routine(void *data)
{
	t_args	*args;

	args = (t_args *) data;
	while (1)
	{
		eat_routine(*args);
		//sleep_routine(*args);
	}
	return (NULL);
}
