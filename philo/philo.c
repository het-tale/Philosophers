/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 20:49:46 by het-tale          #+#    #+#             */
/*   Updated: 2022/09/14 21:25:48 by het-tale         ###   ########.fr       */
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
		pthread_create(&args->philo[i].tid, NULL, &start, &args->philo[i]);
		i++;
	}
	check_death(args);
}

void	join_threads(t_args *args)
{
	int	i;

	i = -1;
	while (++i < args->philo_number)
		pthread_join(args->philo[i].tid, NULL);
}

void	single_philo(t_args *args)
{
	init_philo(args);
	args->start_time = get_time();
	pthread_create(&args->philo[0].tid, NULL, &one_philo, &args->philo[0]);
}

void	*one_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	print_msg("has taken a fork", philo);
	usleep(philo->args->time_to_die * 1000);
	print_msg("died", philo);
	return (NULL);
}
