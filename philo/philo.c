/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 20:49:46 by het-tale          #+#    #+#             */
/*   Updated: 2022/09/14 20:47:35 by het-tale         ###   ########.fr       */
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
	args.end_sim = 0;
	args.died = 0;
	args.number_of_ate_philos = 0;
	pthread_mutex_init(&args.msg_mutex, NULL);
	pthread_mutex_init(&args.fork_mutex, NULL);
	pthread_mutex_init(&args.end_mutex, NULL);
	pthread_mutex_init(&args.eat_mutex, NULL);
	pthread_mutex_init(&args.death_mutex, NULL);
	pthread_mutex_init(&args.lastmeal_mutex, NULL);
	args.fork = malloc(sizeof(t_fork) * args.philo_number);
	i = 0;
	while (i < args.philo_number)
	{
		pthread_mutex_init(&args.fork[i].used_mutex, NULL);
		args.fork[i].used = 0;
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
	if (argc == 6 && (args.number_of_times <= 0))
	{
		printf("invalid arguments\n");
		return (0);
	}
		
	return (1);
}

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
int	main(int argc, char *argv[])
{
	t_args		args;

	if (argc == 5 || argc == 6)
	{
		args = init_args(argc, argv);
		if (!check_errors(args, argc))
			return (0);
		if (args.philo_number == 1)
			single_philo(&args);
		else
			start_simulation(&args);
		join_threads(&args);
	}
	else
		write(2, "Usage : ./philo <arg1> <arg2> <arg3> <arg4> [arg5]\n", 51);
	return (0);
}
