/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 20:49:46 by het-tale          #+#    #+#             */
/*   Updated: 2022/09/13 17:32:58 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*start(void *data)
{
	int	i;
	t_philo	*philo;
	pthread_t	tid;

	philo = (t_philo *)data;
	i = 0;
	philo->max_times_should_eat = 0;
	philo->ate_times = 0;
	philo->expected_death_time = philo->args->time_to_die + philo->args->start_time;
	pthread_create(&tid, NULL, &end_simulation, philo);
	pthread_detach(tid);
	while (i < philo->args->number_of_times || !(philo->args->number_of_times))
	{
		routine(philo);
		i++;
	}
	philo->max_times_should_eat = 1;
	return (NULL);
}

t_args	init_args(int argc, char *argv[])
{
	t_args	args;

	args.philo_number = ft_atoi(argv[1]);
	args.time_to_die = ft_atoi(argv[2]);
	args.time_to_eat = ft_atoi(argv[3]);
	args.time_to_sleep = ft_atoi(argv[4]);
	args.end_sim = 0;
	args.number_of_ate_philos = 0;
	pthread_mutex_init(&args.msg_mutex, NULL);
	if (argc == 6)
		args.number_of_times = ft_atoi(argv[5]);
	else
		args.number_of_times = 0;
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
	if (argc == 6 && !(args.number_of_times))
	{
		printf("invalid arguments\n");
		return (0);
	}
		
	return (1);
}

t_philo	*start_simulation(t_args *args)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = malloc(sizeof(t_philo) * args->philo_number);
	while (i < args->philo_number)
		pthread_mutex_init(&philo[i++].fork_mutex, NULL);
	i = 0;
	while (i < args->philo_number)
	{
		philo[i].philo_id = i + 1;
		philo[i].args = args;
		if (i == args->philo_number - 1)
			philo[i].next_fork_mutex = &philo[0].fork_mutex;
		else
			philo[i].next_fork_mutex = &philo[i + 1].fork_mutex;
		i++;
	}
	i = 0;
	args->start_time = get_time();
	while (i < args->philo_number)
	{
		if (pthread_create(&philo[i].tid, NULL, &start, &philo[i]) != 0)
			return (printf("Thread creation Failed \n"), NULL);
		usleep(20);
		i++;
	}
	i = -1;
	while (++i < args->philo_number)
		pthread_join(philo[i].tid, NULL);
	return (philo);
}

void	*end_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (philo->args->end_sim != 1)
	{
		if (get_time() >= philo->expected_death_time && philo->is_eating != EATING)
		{
			print_msg("died", philo);
			pthread_mutex_lock(&philo->args->msg_mutex);
			philo->args->end_sim = 1;
			break ;
		}
		else if (philo->max_times_should_eat == 1)
		{
			philo->args->number_of_times += 1;
			break ;
		}
	}
	return (NULL);
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
		philo = start_simulation(&args);
		if (!philo)
			return (0);
		// end_simulation(philo, &args);
	}
	else
		write(2, "Usage : ./philo <arg1> <arg2> <arg3> <arg4> [arg5]\n", 51);
	return (0);
}
