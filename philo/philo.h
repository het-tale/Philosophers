/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 20:50:21 by het-tale          #+#    #+#             */
/*   Updated: 2022/09/11 15:41:13 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# define MAX_INT 2147483647

typedef struct s_args	t_args;
typedef struct s_philo	t_philo;

struct s_args
{
	int				philo_number;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times;
	int				id;
	pthread_mutex_t	*forks_mutex;
	int				*used_forks;
	t_philo			*philo;
	pthread_mutex_t	msg_mutex;
	pthread_mutex_t	end_mutex;
	int				end_sim;
};

struct s_philo
{
	pthread_t		tid;
	int				philo_id;
	int				right_i;
	int				left_i;
	pthread_mutex_t	lastmeal_mutex;
	int				lastmeal;
};

int		ft_atoi(const char *str);
void	*routine(void *data);
time_t	get_time(void);
void	print_msg(t_args args, char *str, time_t time);
#endif
