/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 19:29:15 by het-tale          #+#    #+#             */
/*   Updated: 2022/09/10 19:44:12 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
◦ timestamp_in_ms X has taken a fork
◦ timestamp_in_ms X is eating
◦ timestamp_in_ms X is sleeping
◦ timestamp_in_ms X is thinking
◦ timestamp_in_ms X died
**/
time_t  get_time(void)
{
    struct timeval  tv;

    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000)); 
}

void    philo_sleep(t_args args, int time_to)
{
    time_t  awake;

    awake = get_time() + time_to;
    while (get_time() < awake)
    {
        if (args.end_sim == 1)
            break ;
        usleep(100);
    }
    
}

void    eat_routine(t_args args)
{
     time_t  time;

    time = get_time();
    pthread_mutex_lock(&args.forks_mutex[args.philo[args.id].left_i]);
    pthread_mutex_lock(&args.msg_mutex);
    printf("%ld %d has taken a fork\n", time, args.philo[args.id].philo_id);
    pthread_mutex_unlock(&args.msg_mutex);
    pthread_mutex_lock(&args.forks_mutex[args.philo[args.id].right_i]);
    pthread_mutex_lock(&args.msg_mutex);
    printf("%ld %d has taken a fork\n", time, args.philo[args.id].philo_id);
    pthread_mutex_unlock(&args.msg_mutex);
    pthread_mutex_lock(&args.msg_mutex);
    printf("%ld %d is eating\n", time, args.philo[args.id].philo_id);
    pthread_mutex_unlock(&args.msg_mutex);
    pthread_mutex_lock(&args.philo[args.id].lastmeal_mutex);
    args.philo[args.id].lastmeal = get_time();
    pthread_mutex_unlock(&args.philo[args.id].lastmeal_mutex);
    philo_sleep(args, args.time_to_eat);
    pthread_mutex_unlock(&args.forks_mutex[args.philo[args.id].left_i]);
    pthread_mutex_unlock(&args.forks_mutex[args.philo[args.id].right_i]);
}

void    sleep_routine(t_args args)
{
    time_t  time;

    time = get_time();
    pthread_mutex_lock(&args.msg_mutex);
    printf("%ld %d is sleeping\n", time, args.philo[args.id].philo_id);
    pthread_mutex_unlock(&args.msg_mutex);
    philo_sleep(args, args.time_to_sleep);
}

void    *routine(void *data)
{
    t_args  *args;

    args = (t_args *) data;
    while (1)
    {
        eat_routine(*args);
        sleep_routine(*args);
    }
    return (NULL);
}