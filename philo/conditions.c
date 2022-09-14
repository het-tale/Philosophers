/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 16:56:42 by het-tale          #+#    #+#             */
/*   Updated: 2022/09/14 17:08:02 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_args *args)
{
	pthread_mutex_lock(&args->death_mutex);
	if (args->died)
	{
		pthread_mutex_unlock(&args->death_mutex);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&args->death_mutex);
		return (0);
	}
}

int	end_simulation(t_args *args)
{
	pthread_mutex_lock(&args->end_mutex);
	if (args->end_sim)
	{
		pthread_mutex_unlock(&args->end_mutex);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&args->end_mutex);
		return (0);
	}
}

int	is_all_ate(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->eat_mutex);
	if (philo->ate_times >= philo->args->number_of_times)
	{
		pthread_mutex_unlock(&philo->args->eat_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->args->eat_mutex);
	return (0);
}
