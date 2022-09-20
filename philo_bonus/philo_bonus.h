/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 20:50:21 by het-tale          #+#    #+#             */
/*   Updated: 2022/09/20 22:21:20 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <unistd.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <fcntl.h>
# include <semaphore.h>
# include <sys/stat.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# define MAX_INT 2147483647
# define DEAD 13
# define FORKS "/philo_forks"
# define MEAL "/philo_lastmeal"
# define MSG "/philo_msg"
# define END "/philo_end"
# define DEATH "/philo_death"
# define EAT "/philo_eat"
# define USAGE "Usage : ./philo_bonus <arg1> <arg2> <arg3> <arg4> [arg5]\n"

typedef struct s_args	t_args;
typedef struct s_philo	t_philo;

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
	int				number_of_ate_philos;
	sem_t			*sem_forks;
	sem_t			*sem_msg;
	sem_t			*sem_end;
	sem_t			*sem_lastmeal;
	sem_t			*sem_death;
	sem_t			*sem_eat;
	t_philo			*philo;
	pid_t			*pids;
};

struct s_philo
{
	int				philo_id;
	int				ate_times;
	long int		lastmeal;
	t_args			*args;
	pthread_t		tid;
};
//atoi.c
int				ft_atoi(const char *str);
//conditions.c
int				is_dead(t_args *args);
int				end_simulation(t_args *args);
//philo_utils.c
unsigned int	get_time(void);
void			sleep_philo(unsigned int time_to, t_args *args);
//routines.c
void			*start(t_philo *philo);
void			eat_routine(t_philo *philo);
void			print_msg(char *str, t_philo *philo);
void			unlink_local_sem(void);
//philo.c
void			start_simulation(t_args *args);
t_philo			*init_philo(t_args *args);
void			*check_death(void *data);
void			print_death(t_philo *philo);
//main.c
t_args			init_args(int argc, char *argv[]);
int				check_errors(t_args args, int argc);
void			wait_children(t_args *args);
//init_close.c
void			init_global_sem(t_args *args);
void			close_global_sem(t_args *args);
void			unlink_global_sem(void);
void			init_local_sem(t_args *args);
void			close_local_sem(t_args *args);
#endif
