/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 14:25:03 by het-tale          #+#    #+#             */
/*   Updated: 2022/09/20 17:25:17 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_msg(char *str, t_philo *philo)
{
	unsigned int	time_ms;

	sem_wait(philo->args->sem_msg);
	if (!is_dead(philo->args) && !end_simulation(philo->args))
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

void	init_local_sem(t_args *args)
{
	unlink_local_sem();
	args->sem_lastmeal = sem_open("/philo_lastmeal", O_CREAT, S_IRUSR | S_IWUSR, 1);
	args->sem_eat = sem_open("/philo_eat", O_CREAT, S_IRUSR | S_IWUSR, 1);
}

void close_local_sem(t_args *args)
{
	sem_close(args->sem_lastmeal);
	sem_close(args->sem_eat);
	unlink_local_sem();
}

void	unlink_local_sem(void)
{
	sem_unlink("/philo_lastmeal");
	sem_unlink("/philo_eat");
}

void	*start(t_philo *philo)
{
	init_local_sem(philo->args);
	if (philo->philo_id % 2 == 0)
		usleep(1500);
	pthread_create(&philo->tid, NULL, &check_death, philo);
	while (!is_dead(philo->args))
	{
		eat_routine(philo);
		if (end_simulation(philo->args))
			break ;
		print_msg("is sleeping", philo);
		sleep_philo(philo->args->time_to_sleep, philo->args);
		print_msg("is thinking", philo);
	}
	pthread_join(philo->tid, NULL);
	close_global_sem(philo->args);
	close_local_sem(philo->args);
	exit(0);
}
