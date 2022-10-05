/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 17:00:37 by het-tale          #+#    #+#             */
/*   Updated: 2022/10/05 20:16:02 by het-tale         ###   ########.fr       */
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

	(void)args;
	awake = get_time();
	while (get_time() < awake + time_to)
	{
		// if (is_dead(args) || end_simulation(args))
		// 	break ;
		usleep(200);
	}
}
/*
check if all the philosophers ate at least number_of_times time
if so update the end_sim variable
*/

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

int	print_death(t_args *args, int i)
{
	unsigned int	time;

	pthread_mutex_lock(&args->msg_mutex);
	time = get_time() - args->start_time - 1;
	printf("%u %d %s\n", time, args->philo[i].philo_id, "died");
	pthread_mutex_unlock(&args->msg_mutex);
	return (1);
}

/*
while the simulation has not ended:
*check for each philosopher if he doesn't eat more than time_to_die 
if so update the death variable and print death.
*check if all philos have eaten number_of_times times;
*/

int	check_death(t_args *args)
{
	int	i;
	int	d;

	while (!end_simulation(args))
	{
		i = -1;
		while (++i < args->philo_number && !is_dead(args))
		{
			pthread_mutex_lock(&args->lastmeal_mutex);
			if (get_time() - args->philo[i].lastmeal > args->time_to_die)
			{
				pthread_mutex_lock(&args->death_mutex);
				args->died = 1;
				pthread_mutex_unlock(&args->death_mutex);
				d = print_death(args, i);
			}
			pthread_mutex_unlock(&args->lastmeal_mutex);
		}
		if (is_dead(args))
			break ;
		is_max_ate(args);
	}
	return (d);
}
