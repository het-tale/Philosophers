/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 21:22:14 by het-tale          #+#    #+#             */
/*   Updated: 2022/10/06 21:06:41 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_mutexes(t_args *args)
{
	int	i;

	i = -1;
	pthread_mutex_init(&args->msg_mutex, NULL);
	pthread_mutex_init(&args->end_mutex, NULL);
	pthread_mutex_init(&args->eat_mutex, NULL);
	pthread_mutex_init(&args->death_mutex, NULL);
	pthread_mutex_init(&args->lastmeal_mutex, NULL);
	args->fork = malloc(sizeof(pthread_mutex_t) * args->philo_number);
	while (++i < args->philo_number)
		pthread_mutex_init(&args->fork[i], NULL);
}

t_args	*init_args(int argc, char *argv[])
{
	t_args	*args;

	args = malloc(sizeof(t_args));
	args->philo_number = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	args->end_sim = 0;
	args->died = 0;
	if (argc == 6)
		args->number_of_times = ft_atoi(argv[5]);
	else
		args->number_of_times = -1;
	if (!check_errors(*args, argc))
		return (NULL);
	init_mutexes(args);
	return (args);
}

int	check_errors(t_args args, int argc)
{
	if ((args.philo_number <= 0 || args.philo_number > 200)
		|| args.time_to_die < 60 || args.time_to_eat < 60
		|| args.time_to_sleep < 60)
	{
		ft_putstr_fd(2, "invalid arguments\n");
		return (0);
	}
	if (argc == 6 && (args.number_of_times <= 0))
	{
		ft_putstr_fd(2, "invalid arguments\n");
		return (0);
	}
	return (1);
}

void	destroy_mutexes(t_args *args)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&args->msg_mutex);
	pthread_mutex_destroy(&args->end_mutex);
	pthread_mutex_destroy(&args->eat_mutex);
	pthread_mutex_destroy(&args->death_mutex);
	pthread_mutex_destroy(&args->lastmeal_mutex);
	while (++i < args->philo_number)
		pthread_mutex_destroy(&args->fork[i]);
}

int	main(int argc, char *argv[])
{
	t_args		*args;

	args = NULL;
	if (argc == 5 || argc == 6)
	{
		args = init_args(argc, argv);
		if (!args)
			return (EXIT_FAILURE);
		start_simulation(args);
		if (check_death(args))
			return (EXIT_SUCCESS);
		join_threads(args);
		destroy_mutexes(args);
	}
	else
	{
		ft_putstr_fd(2, USAGE);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
