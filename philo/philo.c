/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 20:49:46 by het-tale          #+#    #+#             */
/*   Updated: 2022/09/12 12:52:22 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_args	init_args(int argc, char *argv[])
{
	t_args	args;
	int		i;

	args.philo_number = ft_atoi(argv[1]);
	args.time_to_die = ft_atoi(argv[2]);
	args.time_to_eat = ft_atoi(argv[3]);
	args.time_to_sleep = ft_atoi(argv[4]);
	args.forks_mutex = malloc(sizeof(pthread_mutex_t) * args.philo_number);
	//args.philo = malloc(sizeof(t_philo) * args.philo_number);
	args.end_sim = 0;
	pthread_mutex_init(&args.msg_mutex, NULL);
	i = 0;
	while (i < args.philo_number)
	{
		pthread_mutex_init(&args.forks_mutex[i], NULL);
		i++;
	}
	if (argc == 6)
		args.number_of_times = ft_atoi(argv[5]);
	else
		args.number_of_times = -1;
	return (args);
}

int	check_errors(t_args args, int argc)
{
	if ((args.philo_number <= 0 || args.philo_number > 200)
		|| args.time_to_die < 60 || args.time_to_eat < 60
		|| args.time_to_sleep < 60)
	{
		printf("invalid arguments\n");
		return (0);
	}
	if (argc == 6 && args.number_of_times < 0)
	{
		printf("invalid arguments\n");
		return (0);
	}
		
	return (1);
}

t_philo	*init_philo(t_args args)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = malloc(sizeof(t_philo) * args.philo_number);
	while (i < args.philo_number)
	{
		philo[i].philo_id = i;
		philo[i].args = args;
		pthread_mutex_init(&philo[i].lastmeal_mutex, NULL);
		philo[i].lastmeal = get_time();
		philo[i].ate_times = 0;
		philo[i].is_eating = 0;
		i++;
	}
	return (philo);
}

int	create_threads(t_args	*args, t_philo	*philo)
{
	int	i;

	i = 0;
	while (i < args->philo_number)
	{
		pthread_create(&philo[i].tid, NULL, &routine, &philo[i]);
		i++;
	}
	return (0);
}

void	end_simulation(t_philo *philo, t_args args)
{
	int	i;

	i = 0;
	while (i < args.philo_number)
	{
		pthread_join(philo[i].tid, NULL);
		i++;
	}
	free(philo);
	free(args.forks_mutex);
}

int	main(int argc, char *argv[])
{
	t_args		args;
	t_philo		*philo;

	if (argc == 5 || argc == 6)
	{
		args = init_args(argc, argv);
		if (!check_errors(args, argc))
			return (0);
		philo = init_philo(args);
		if (create_threads(&args, philo))
			return (1);
		end_simulation(philo, args);
	}
	else
		write(2, "Usage : ./philo <arg1> <arg2> <arg3> <arg4> [arg5]\n", 51);
	return (0);
}
