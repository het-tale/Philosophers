/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 20:49:46 by het-tale          #+#    #+#             */
/*   Updated: 2022/10/06 12:16:12 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_philo	*init_philo(t_args *args)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = malloc(sizeof(t_philo) * args->philo_number);
	while (i < args->philo_number)
	{
		philo[i].philo_id = i + 1;
		philo[i].ate_times = 0;
		philo[i].lastmeal = 0;
		philo[i].args = args;
		i++;
	}
	return (philo);
}

void	start_simulation(t_args *args)
{
	int		i;
	pid_t	pid;
	t_philo	*philo;

	i = 0;
	philo = init_philo(args);
	args->philo = philo;
	args->start_time = get_time();
	while (i < args->philo_number)
	{
		args->philo[i].lastmeal = args->start_time;
		pid = fork();
		if (pid == -1)
			printf("error\n");
		else if (pid > 0)
			args->pids[i] = pid;
		else if (pid == 0)
			start(&args->philo[i]);
		i++;
	}
}

int	is_dead(t_args *args)
{
	sem_wait(args->sem_death);
	if (args->died)
	{
		sem_post(args->sem_death);
		return (1);
	}
	else
	{
		sem_post(args->sem_death);
		return (0);
	}
}

void	print_death(t_philo *philo)
{
	unsigned int	time;

	sem_wait(philo->args->sem_msg);
	time = get_time() - philo->args->start_time;
	printf("%u %d %s\n", time, philo->philo_id, "died");
	// sem_post(philo->args->sem_msg);
}

void	*check_death(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (1)
	{
		sem_wait(philo->args->sem_lastmeal);
		if (get_time() - philo->lastmeal > philo->args->time_to_die)
		{
			print_death(philo);
			sem_wait(philo->args->sem_death);
			philo->args->died = 1;
			sem_post(philo->args->sem_death);
			exit(DEAD);
		}
		sem_post(philo->args->sem_lastmeal);
		if (is_dead(philo->args))
			break ;
		if (philo->args->number_of_times != -1
			&& philo->ate_times >= philo->args->number_of_times)
			break ;
	}
	return (NULL);
}
