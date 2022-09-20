/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 21:22:14 by het-tale          #+#    #+#             */
/*   Updated: 2022/09/20 17:16:51 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_args	init_args(int argc, char *argv[])
{
	t_args	args;

	args.philo_number = ft_atoi(argv[1]);
	args.time_to_die = ft_atoi(argv[2]);
	args.time_to_eat = ft_atoi(argv[3]);
	args.time_to_sleep = ft_atoi(argv[4]);
	args.end_sim = 0;
	args.died = 0;
	args.pids = malloc(sizeof(pid_t) * args.philo_number);
	init_global_sem(&args);
	args.number_of_ate_philos = 0;
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

void	init_global_sem(t_args *args)
{
	unlink_global_sem();
	args->sem_forks = sem_open("/philo_forks", O_CREAT, S_IRUSR | S_IWUSR, args->philo_number);
	args->sem_msg = sem_open("/philo_msg", O_CREAT, S_IRUSR | S_IWUSR, 1);
	args->sem_end = sem_open("/philo_end", O_CREAT, S_IRUSR | S_IWUSR, 1);
	args->sem_death = sem_open("/philo_death", O_CREAT, S_IRUSR | S_IWUSR, 1);
}

void close_global_sem(t_args *args)
{
	sem_close(args->sem_forks);
	sem_close(args->sem_msg);
	sem_close(args->sem_end);
	sem_close(args->sem_death);
	unlink_global_sem();
}

void	unlink_global_sem(void)
{
	sem_unlink("/philo_forks");
	sem_unlink("/philo_msg");
	sem_unlink("/philo_end");
	sem_unlink("/philo_death");
}

void	wait_children(t_args *args)
{
	int	i;
	int	status;

	i = 0;
	while (i < args->philo_number)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status))
		{
			i = -1;
			while (++i < args->philo_number)
				kill(args->pids[i], SIGKILL);
			break ;
		}
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_args		args;

	if (argc == 5 || argc == 6)
	{
		args = init_args(argc, argv);
		if (!check_errors(args, argc))
			return (0);
		start_simulation(&args);
		wait_children(&args);
		close_global_sem(&args);
	}
	else
		write(2, "Usage : ./philo_bonus <arg1> <arg2> <arg3> <arg4> [arg5]\n", 57);
	return (0);
}
