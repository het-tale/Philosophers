/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 20:50:21 by het-tale          #+#    #+#             */
/*   Updated: 2022/10/05 10:26:24 by het-tale         ###   ########.fr       */
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
# define USAGE "Usage : ./philo <arg1> <arg2> <arg3> <arg4> [arg5]\n"

typedef struct s_args	t_args;
typedef struct s_philo	t_philo;
typedef struct s_fork	t_fork;

struct s_fork
{
	pthread_mutex_t		used_mutex;
	int					used;
};

struct s_args
{
	int				philo_number;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times;
	int				end_sim;
	int				died;
	unsigned int	start_time;
	pthread_mutex_t	msg_mutex;
	pthread_mutex_t	eat_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	end_mutex;
	pthread_mutex_t	lastmeal_mutex;
	t_philo			*philo;
	t_fork			*fork;
};

struct s_philo
{
	int				philo_id;
	int				left_i;
	int				right_i;
	pthread_t		tid;
	int				ate_times;
	t_args			*args;
	long int		lastmeal;
};
//atoi.c
int				ft_atoi(const char *str);
//conditions.c
int				is_dead(t_args *args);
int				end_simulation(t_args *args);
int				is_all_ate(t_philo *philo);
void			ft_putstr_fd(int fd, char *str);
//philo_utils.c
unsigned int	get_time(void);
void			sleep_philo(unsigned int time_to, t_args *args);
void			check_death(t_args *args);
void			print_death(t_args *args, int i);
//routines.c
void			*start(void *data);
void			eat_routine(t_philo *philo);
int				pick_fork(t_philo *philo, t_fork *fork);
void			put_fork_down(t_fork *fork);
void			print_msg(char *str, t_philo *philo);
//philo.c
void			start_simulation(t_args *args);
void			*one_philo(void *data);
void			single_philo(t_args *args);
void			join_threads(t_args *args);
void			init_philo(t_args *args);
//main.c
t_args			*init_args(int argc, char *argv[]);
int				check_errors(t_args args, int argc);
void			init_mutexes(t_args *args);
#endif
