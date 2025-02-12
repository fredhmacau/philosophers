/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmacau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:31:06 by fmacau            #+#    #+#             */
/*   Updated: 2025/02/12 10:31:07 by fmacau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

int    check_death(t_philo *philo)
{
    long current_time;

    current_time = ft_current_time();
    if (current_time - philo->last_meal_time >= philo->data->time_to_die)
    {
        pthread_mutex_lock(&philo->data->print_logs);
        printf("%ld %d died\n", current_time - philo->data->start_time, philo->id);
        pthread_mutex_unlock(&philo->data->print_logs);
        philo->data->stop_simulation = 1;
        return (1);
    }
    return (0);
}

void    take_forks(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->forks[philo->id - 1]);
    log_message(philo, "has taken a fork");
    if (check_death(philo))
    {
        pthread_mutex_unlock(&philo->data->forks[philo->id - 1]);
        return ;
    }
    pthread_mutex_lock(&philo->data->forks[philo->id % philo->data->num_philosophers]);
    log_message(philo, "has taken a fork");
}

void    eat(t_philo *philo)
{
    log_message(philo, "is eating");
    usleep(philo->data->time_to_eat * 1000);
    philo->last_meal_time = ft_current_time();
    philo->eating++;
}

void    put_down_forks(t_philo *philo)
{
    pthread_mutex_unlock(&philo->data->forks[philo->id - 1]);
    pthread_mutex_unlock(&philo->data->forks[philo->id % philo->data->num_philosophers]);
}

void    sleep_and_think(t_philo *philo)
{
    log_message(philo, "is sleeping");
    usleep(philo->data->time_to_sleep * 1000);
    log_message(philo, "is thinking");
}