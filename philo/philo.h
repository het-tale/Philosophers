/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 20:50:21 by het-tale          #+#    #+#             */
/*   Updated: 2022/09/10 19:33:34 by het-tale         ###   ########.fr       */
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
	int	philo_number;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times;
	int				id;
	pthread_mutex_t	*forks_mutex;
	t_philo	*philo;
	pthread_mutex_t	msg_mutex;
	pthread_mutex_t	end_mutex;
	int	end_sim;
};

struct s_philo
{
	int				philo_id;
	int				right_i;
	int				left_i;
	pthread_mutex_t	lastmeal_mutex;
	int				lastmeal;
};

int		ft_atoi(const char *str);
void	*routine(void *data);
time_t	get_time(void);
#endif

/*
# create n threads
{
	i = get thread id;

	if i % 2 == 0:  //avoid deadlock
		usleep(100); 
	while (1)
	{
		synch data //mutexes
		eat
		sleep
		think
	}
}
while (i < n) //main thread
	symch data 
	if philo[i]->died:
		mutex_end_of_simulation //global mutex initiated before thread creation
		print(i died);
		return 1;
	
#join n threads

*/