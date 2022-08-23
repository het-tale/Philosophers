/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 20:49:46 by het-tale          #+#    #+#             */
/*   Updated: 2022/08/23 02:22:19 by het-tale         ###   ########.fr       */
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
	if (argc == 6)
		args.number_of_times = ft_atoi(argv[5]);
	return (args);
}

int	main(int argc, char *argv[])
{
	t_args	args;

	if (argc == 5 || argc == 6)
	{
		args = init_args(argc, argv);
		if ((args.philo_number <= 0 || args.philo_number > 200)
			|| args.time_to_die < 60 || args.time_to_eat < 60
			|| args.time_to_sleep < 60 || args.number_of_times < 0)
		{
			printf("invalid arguments\n");
			return (0);
		}
	}
	return (0);
}
