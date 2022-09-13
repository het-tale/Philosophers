/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 14:25:03 by het-tale          #+#    #+#             */
/*   Updated: 2022/09/13 17:15:32 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void    sleep_philo(unsigned int time_to)
{
        unsigned int    awake;

        awake = get_time();
        while (get_time() < awake + time_to / 1000)
            usleep(80);
}

void    print_msg(char *str, t_philo *philo)
{
    unsigned int    time_ms;

    pthread_mutex_lock(&philo->args->msg_mutex);
    time_ms = get_time() - philo->args->start_time;
    printf("%u %d %s\n", time_ms, philo->philo_id, str);
    pthread_mutex_unlock(&philo->args->msg_mutex);
}

void    routine(t_philo *philo)
{
    pthread_mutex_lock(&philo->fork_mutex);
    print_msg("has taken a fork", philo);
    pthread_mutex_lock(philo->next_fork_mutex);
    print_msg("has taken a fork", philo);
    philo->is_eating = EATING;
    philo->ate_times += 1;
    print_msg("is eating", philo);
    philo->expected_death_time = get_time() + philo->args->time_to_die;
    sleep_philo(philo->args->time_to_eat * 1000);
    pthread_mutex_unlock(&philo->fork_mutex);
    pthread_mutex_unlock(philo->next_fork_mutex);
    philo->is_eating = NOT_EATING;
    if (philo->ate_times >= philo->args->number_of_ate_philos && philo->args->number_of_times)
        return ;
    print_msg("is sleeping", philo);
    sleep_philo(philo->args->time_to_sleep * 1000);
    print_msg("is thinking", philo);
}