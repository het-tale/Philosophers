/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 21:22:14 by het-tale          #+#    #+#             */
/*   Updated: 2022/10/06 12:23:20 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_args	*init_args(int argc, char *argv[])
{
	t_args	*args;

	args = malloc(sizeof(t_args));
	args->philo_number = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	args->died = 0;
	if (argc == 6)
		args->number_of_times = ft_atoi(argv[5]);
	else
		args->number_of_times = -1;
	if (!check_errors(*args, argc))
		return (NULL);
	args->pids = malloc(sizeof(pid_t) * args->philo_number);
	init_global_sem(args);
	return (args);
}

int	check_errors(t_args args, int argc)
{
	if ((args.philo_number <= 0 || args.philo_number > 200)
		|| args.time_to_die < 60 || args.time_to_eat < 60
		|| args.time_to_sleep < 60)
	{
		ft_putstr_fd(2, "Invalid arguments\n");
		return (0);
	}
	if (argc == 6 && (args.number_of_times <= 0))
	{
		ft_putstr_fd(2, "Invalid arguments\n");
		return (0);
	}
	return (1);
}

void	wait_children(t_args *args)
{
	int	i;
	int	status;

	i = 0;
	while (i < args->philo_number)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) == DEAD)
		{
			i = -1;
			while (++i < args->philo_number)
				kill(args->pids[i], SIGKILL);
			break ;
		}
		i++;
	}
}

void	ft_putstr_fd(int fd, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
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
		wait_children(args);
		close_global_sem(args);
	}
	else
	{
		ft_putstr_fd(2, USAGE);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
