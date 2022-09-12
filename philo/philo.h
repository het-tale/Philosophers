/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 20:50:21 by het-tale          #+#    #+#             */
/*   Updated: 2022/09/12 16:29:47 by het-tale         ###   ########.fr       */
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
	pthread_mutex_t	*forks_mutex;
	pthread_mutex_t	msg_mutex;
	int				end_sim;
	unsigned int	start_time;
};

struct s_philo
{
	int				philo_id;
	pthread_t		tid;
	pthread_mutex_t	lastmeal_mutex;
	int				lastmeal;
	int				ate_times;
	int				is_eating;
	t_args			args;
	pthread_mutex_t	fork_mutex;
	pthread_mutex_t	*next_fork_mutex;
};

int		ft_atoi(const char *str);
void	*routine(void *data);
time_t	get_time(void);
void	print_msg(char *str, t_philo philo);
#endif
