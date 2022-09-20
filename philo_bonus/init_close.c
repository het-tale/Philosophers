/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_close.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 21:41:06 by het-tale          #+#    #+#             */
/*   Updated: 2022/09/20 22:20:04 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_global_sem(t_args *args)
{
	int	number;

	number = args->philo_number;
	unlink_global_sem();
	args->sem_forks = sem_open(FORKS, O_CREAT, S_IRUSR | S_IWUSR, number);
	args->sem_msg = sem_open(MSG, O_CREAT, S_IRUSR | S_IWUSR, 1);
	args->sem_end = sem_open(END, O_CREAT, S_IRUSR | S_IWUSR, 1);
	args->sem_death = sem_open(DEATH, O_CREAT, S_IRUSR | S_IWUSR, 1);
}

void	close_global_sem(t_args *args)
{
	sem_close(args->sem_forks);
	sem_close(args->sem_msg);
	sem_close(args->sem_end);
	sem_close(args->sem_death);
	unlink_global_sem();
	free(args->pids);
	free(args->philo);
}

void	unlink_global_sem(void)
{
	sem_unlink(FORKS);
	sem_unlink(MSG);
	sem_unlink(END);
	sem_unlink(DEATH);
}

void	init_local_sem(t_args *args)
{
	unlink_local_sem();
	args->sem_lastmeal = sem_open(MEAL, O_CREAT, S_IRUSR | S_IWUSR, 1);
	args->sem_eat = sem_open(EAT, O_CREAT, S_IRUSR | S_IWUSR, 1);
}

void	close_local_sem(t_args *args)
{
	sem_close(args->sem_lastmeal);
	sem_close(args->sem_eat);
	unlink_local_sem();
}
