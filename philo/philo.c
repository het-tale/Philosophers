/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 20:49:46 by het-tale          #+#    #+#             */
/*   Updated: 2022/09/11 13:18:54 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_args	init_args(int argc, char *argv[])
{
	t_args	args;

	args.philo_number = ft_atoi(argv[1]);
	args.time_to_die = ft_atoi(argv[2]);
	args.time_to_eat = ft_atoi(argv[3]);
	args.time_to_sleep = ft_atoi(argv[4]);
	args.forks_mutex = malloc(sizeof(pthread_mutex_t) * args.philo_number);
	args.philo = malloc(sizeof(t_philo) * args.philo_number);
	args.end_sim = 0;
	if (argc == 6)
		args.number_of_times = ft_atoi(argv[5]);
	return (args);
}

int	check_errors(t_args args)
{
	if ((args.philo_number <= 0 || args.philo_number > 200)
		|| args.time_to_die < 60 || args.time_to_eat < 60
		|| args.time_to_sleep < 60 || args.number_of_times < 0)
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
	philo = args.philo;
	while (i < args.philo_number)
	{
		philo[i].philo_id = i + 1;
		philo[i].left_i = i;
		philo[i].right_i = ((i + 1) % args.philo_number);
		i++;
	}
	return (philo);
}

int	main(int argc, char *argv[])
{
	t_args		args;
	int			i;
	pthread_t	*tid;

	if (argc == 5 || argc == 6)
	{
		i = 0;
		args = init_args(argc, argv);
		if (!check_errors(args))
			return (0);
		args.philo = init_philo(args);
		tid = malloc(sizeof(pthread_t) * args.philo_number);
		pthread_mutex_init(&args.msg_mutex, NULL);
		pthread_mutex_init(&args.end_mutex, NULL);
		i = 0;
		while (i < args.philo_number)
		{
			pthread_mutex_init(&args.philo[i].lastmeal_mutex, NULL);
			i++;
		}
		i = 0;
		while (i < args.philo_number)
		{
			pthread_mutex_init(&args.forks_mutex[args.philo[i].left_i], NULL);
			pthread_mutex_init(&args.forks_mutex[args.philo[i].right_i], NULL);
			i++;
		}
		i = 0;
		while (i < args.philo_number)
		{
			args.id = i;
			pthread_create(&tid[i], NULL, routine, &args);
			i++;
		}
		i = 0;
		while (i < args.philo_number)
		{
			pthread_join(tid[i], NULL);
			i++;
		}
	}
	else
		write(2, "Usage : ./philo <arg1> <arg2> <arg3> <arg4> [arg5]\n", 51);
	return (0);
}
