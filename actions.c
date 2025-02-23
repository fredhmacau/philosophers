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

void lock_forks(t_philo *philo, int left_fork, int right_fork) {
    if (philo->id % 2 == 0) {
        pthread_mutex_lock(&philo->data->forks[left_fork]);
        log_message(philo, "has taken a fork");
        pthread_mutex_lock(&philo->data->forks[right_fork]);
        log_message(philo, "has taken a fork");
    } else {
        pthread_mutex_lock(&philo->data->forks[right_fork]);
        log_message(philo, "has taken a fork");
        pthread_mutex_lock(&philo->data->forks[left_fork]);
        log_message(philo, "has taken a fork");
    }
}

void unlock_forks(t_philo *philo, int left_fork, int right_fork) {
    pthread_mutex_unlock(&philo->data->forks[left_fork]);
    pthread_mutex_unlock(&philo->data->forks[right_fork]);
}


void eat(t_philo *philo) {
    int left_fork;
    int right_fork;
    
    left_fork = philo->id;
    right_fork = (philo->id + 1) % philo->data->num_philosophers;
    if (philo->data->stop_simulation)
        return;
    lock_forks(philo, left_fork, right_fork);
    if (philo->data->stop_simulation) {
        unlock_forks(philo, left_fork, right_fork);
        return;
    }
    pthread_mutex_lock(&philo->data->meal_sync);
    philo->last_meal_time = ft_current_time();
    philo->eating++;
    pthread_mutex_unlock(&philo->data->meal_sync);
    log_message(philo, "is eating");
    precise_usleep(philo->data->time_to_eat, philo->data);
    unlock_forks(philo, left_fork, right_fork);
}

void    sleep_and_think(t_philo *philo)
{
    if (philo->data->stop_simulation) {
        return;
    }
    log_message(philo, "is sleeping");
    precise_usleep(philo->data->time_to_sleep, philo->data);
    if (philo->data->stop_simulation) {
        return;
    }
    log_message(philo, "is thinking");
}