/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 14:25:03 by het-tale          #+#    #+#             */
/*   Updated: 2022/10/06 12:15:08 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_msg(char *str, t_philo *philo)
{
	unsigned int	time_ms;

	sem_wait(philo->args->sem_msg);
	if (!is_dead(philo->args))
	{
		time_ms = get_time() - philo->args->start_time;
		printf("%u %d %s\n", time_ms, philo->philo_id, str);
	}
	sem_post(philo->args->sem_msg);
}

void	eat_routine(t_philo *philo)
{
	sem_wait(philo->args->sem_forks);
	print_msg("has taken a fork", philo);
	sem_wait(philo->args->sem_forks);
	print_msg("has taken a fork", philo);
	sem_wait(philo->args->sem_lastmeal);
	print_msg("is eating", philo);
	philo->lastmeal = get_time();
	sem_post(philo->args->sem_lastmeal);
	sleep_philo(philo->args->time_to_eat, philo->args);
	sem_wait(philo->args->sem_eat);
	philo->ate_times++;
	sem_post(philo->args->sem_eat);
	sem_post(philo->args->sem_forks);
	sem_post(philo->args->sem_forks);
}

void	unlink_local_sem(void)
{
	sem_unlink(MEAL);
	sem_unlink(EAT);
}

void	*start(t_philo *philo)
{
	init_local_sem(philo->args);
	pthread_create(&philo->tid, NULL, &check_death, philo);
	while (!is_dead(philo->args))
	{
		eat_routine(philo);
		if (philo->args->number_of_times != -1
			&& philo->ate_times >= philo->args->number_of_times)
			break ;
		print_msg("is sleeping", philo);
		sleep_philo(philo->args->time_to_sleep, philo->args);
		print_msg("is thinking", philo);
	}
	close_local_sem(philo->args);
	exit(0);
}
