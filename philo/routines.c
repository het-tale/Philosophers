/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 14:25:03 by het-tale          #+#    #+#             */
/*   Updated: 2022/10/05 20:23:39 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_msg(char *str, t_philo *philo)
{
	unsigned int	time_ms;

	pthread_mutex_lock(&philo->args->msg_mutex);
	if (!is_dead(philo->args) && !end_simulation(philo->args))
	{
		time_ms = get_time() - philo->args->start_time;
		printf("%u %d %s\n", time_ms, philo->philo_id, str);
	}
	pthread_mutex_unlock(&philo->args->msg_mutex);
}

void	put_fork_down(t_fork *fork)
{
	pthread_mutex_lock(&fork->used_mutex);
	fork->used = 0;
	pthread_mutex_unlock(&fork->used_mutex);
}

int	pick_fork(t_philo *philo, t_fork *fork)
{
	pthread_mutex_lock(&fork->used_mutex);
	if (!fork->used)
	{
		print_msg("has taken a fork", philo);
		fork->used = philo->philo_id;
	}
	if (fork->used == philo->philo_id)
	{
		pthread_mutex_unlock(&fork->used_mutex);
		return (1);
	}
	pthread_mutex_unlock(&fork->used_mutex);
	return (0);
}

/*
a philosopher can only pick a fork if it's available if not the philosopher 
should wait until the fork is available
this function updates lastmeal and times each philo ate
*/

void	eat_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->fork[philo->left_i]);
	print_msg("has taken a fork", philo);
	pthread_mutex_lock(&philo->args->fork[philo->right_i]);
	print_msg("has taken a fork", philo);
	pthread_mutex_lock(&philo->args->lastmeal_mutex);
	philo->lastmeal = get_time();
	print_msg("is eating", philo);
	pthread_mutex_unlock(&philo->args->lastmeal_mutex);
	sleep_philo(philo->args->time_to_eat, philo->args);
	pthread_mutex_lock(&philo->args->eat_mutex);
	philo->ate_times++;
	pthread_mutex_unlock(&philo->args->eat_mutex);
	pthread_mutex_unlock(&philo->args->fork[philo->left_i]);
	pthread_mutex_unlock(&philo->args->fork[philo->right_i]);
}
/*routine of each philosopher the philosophers eat, sleep and think while 
a philo is not dead or the simulation has not ended yet (each philo ate
at least number of times)
*/

void	*start(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->philo_id % 2 == 0)
		usleep(100);
	while (1)
	{
		eat_routine(philo);
		if (end_simulation(philo->args))
			break ;
		print_msg("is sleeping", philo);
		sleep_philo(philo->args->time_to_sleep, philo->args);
		print_msg("is thinking", philo);
	}
	return (NULL);
}
