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

typedef struct s_philo
{
    int     id;
    int     time_to_die;
    int     time_to_eat;
    int     time_to_sleep;
    int     nbr_of_meals;
    int     nbr_of_philo;
    int     *forks;
    int     *meals;
}   t_philo;

typedef struct s_data
{
    t_philo *philo;
    int     nbr_of_philo;
    int     nbr_of_meals;
    int     time_to_die;
    int     time_to_eat;
    int     time_to_sleep;
    pthread_t   *thread;
    pthread_mutex_t *mutex;
    pthread_mutex_t *forks;
    pthread_mutex_t *meals;
}   t_data;

int ft_isdigit(int c);
int ft_atoi(char *str);
int ft_checker_input(char **av);
#endif