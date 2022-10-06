/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 20:49:46 by het-tale          #+#    #+#             */
/*   Updated: 2022/10/06 21:00:22 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_args *args)
{
	int		i;

	i = 0;
	args->philo = malloc(sizeof(t_philo) * args->philo_number);
	while (i < args->philo_number)
	{
		args->philo[i].philo_id = i + 1;
		args->philo[i].args = args;
		args->philo[i].ate_times = 0;
		args->philo[i].right_i = i;
		args->philo[i].left_i = (i + 1) % args->philo_number;
		args->philo[i].lastmeal = 0;
		i++;
	}
}

void	start_simulation(t_args *args)
{
	int		i;

	i = 0;
	init_philo(args);
	args->start_time = get_time();
	while (i < args->philo_number)
	{
		args->philo[i].lastmeal = args->start_time;
		if (pthread_create(&args->philo[i].tid, NULL, &start, &args->philo[i]))
			ft_putstr_fd(2, "Failed to create Thread\n");
		i++;
	}
}

void	join_threads(t_args *args)
{
	int	i;

	i = -1;
	while (++i < args->philo_number)
		if (pthread_join(args->philo[i].tid, NULL))
			ft_putstr_fd(2, "Failed to Join Thread\n");
	free(args->fork);
	free(args->philo);
}
