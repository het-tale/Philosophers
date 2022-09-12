/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 19:29:15 by het-tale          #+#    #+#             */
/*   Updated: 2022/09/12 16:51:41 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// /**
// ◦ timestamp_in_ms X has taken a fork
// ◦ timestamp_in_ms X is eating
// ◦ timestamp_in_ms X is sleeping
// ◦ timestamp_in_ms X is thinking
// ◦ timestamp_in_ms X died
// **/
time_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void    philo_sleep(int time_to)
{
        time_t  awake;

        awake = get_time() + time_to;
        while (get_time() < awake)
        {
                usleep(100);
        }
}

void	print_msg(char *str, t_philo philo)
{
	pthread_mutex_lock(&philo.args.msg_mutex);
	printf("%ld %d %s\n", get_time(), (philo.philo_id + 1), str);
	pthread_mutex_unlock(&philo.args.msg_mutex);
}

void	pick_fork(t_philo philo)
{
	pthread_mutex_lock(&philo.fork_mutex);
	print_msg("has taken a fork", philo);
	pthread_mutex_lock(philo.next_fork_mutex);
	print_msg("has taken a fork", philo);
}

void	eat_routine(t_philo philo)
{
	philo.ate_times++;
	philo.lastmeal = get_time();
	print_msg("is eating", philo);
	pthread_mutex_lock(&philo.lastmeal_mutex);
	philo.is_eating = 1;
	philo_sleep(philo.args.time_to_eat);
	pthread_mutex_unlock(&philo.lastmeal_mutex);
	philo.is_eating = 0;
}

void	sleep_routine(t_philo philo)
{
	print_msg("is sleeping", philo);
	pthread_mutex_unlock(&philo.fork_mutex);
	pthread_mutex_unlock(philo.next_fork_mutex);
	philo_sleep(philo.args.time_to_sleep);
}

void	*routine(void *data)
{
	t_philo	philo;

	philo = *(t_philo *) data;
	if (philo.philo_id % 2)
		usleep(100);
	while (1)
	{
		pick_fork(philo);
		eat_routine(philo);
		sleep_routine(philo);
		print_msg("is thinking", philo);
	}
	return (NULL);
}
