/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmacau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:31:51 by fmacau            #+#    #+#             */
/*   Updated: 2025/01/28 16:31:52 by fmacau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/time.h>
# define ERROR "\x1b[31m"
# define EATING "\x1b[32m"
# define SLEEPING "\x1b[35m"
# define DIE "\x1b[38;5;1m"

typedef struct s_philo
{
    int id;
    int eating;
    long last_meal_time;
    pthread_t thread;
    struct s_data *data;
}   t_philo;

typedef struct s_data
{
    int num_philosophers;
    long time_to_die;
    long time_to_eat;
    long time_to_sleep;
    long start_time;
    int must_eat_count;
    int stop_simulation;
    int num_philo_who_ate;
    pthread_t supervisor;
    pthread_mutex_t *forks;
    pthread_mutex_t print_logs;
    pthread_mutex_t meal_sync;
    pthread_mutex_t stop_simulation_mutex;
    t_philo *philosophers;
}   t_data;

int ft_isdigit(int c);
int ft_atoi(char *str);
int ft_checker_input(char **av);
int ft_parse_args(t_data *data, int ac, char **av);
int ft_init_data(t_data *data);
long ft_current_time(void);
void    log_message(t_philo *philo, char *action);
// void    put_down_forks(t_philo *philo);
void    sleep_and_think(t_philo *philo);
void    eat(t_philo *philo);
void    start_simulation(t_data *data);
void cleanup(t_data *data);
void precise_usleep(long usec, t_data *data);
void *supervisor(void *arg);
// void acquire_permission(t_data *data);
// void release_permission(t_data *data);
#endif