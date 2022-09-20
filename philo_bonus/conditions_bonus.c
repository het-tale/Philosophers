/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditions_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 16:56:42 by het-tale          #+#    #+#             */
/*   Updated: 2022/09/20 21:34:41 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	is_dead(t_args *args)
{
	sem_wait(args->sem_death);
	if (args->died)
	{
		sem_post(args->sem_death);
		return (1);
	}
	else
	{
		sem_post(args->sem_death);
		return (0);
	}
}

int	end_simulation(t_args *args)
{
	sem_wait(args->sem_end);
	if (args->end_sim)
	{
		sem_post(args->sem_end);
		return (1);
	}
	else
	{
		sem_post(args->sem_end);
		return (0);
	}
}
