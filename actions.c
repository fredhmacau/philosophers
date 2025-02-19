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

int check_death(t_philo *philo)
{
    long current_time;

    current_time = ft_current_time();
    pthread_mutex_lock(&philo->data->stop_simulation_mutex);
    if (current_time - philo->last_meal_time >= philo->data->time_to_die)
    {
        pthread_mutex_unlock(&philo->data->stop_simulation_mutex);
        pthread_mutex_lock(&philo->data->print_logs);
        printf("%ld %d died\n", current_time - philo->data->start_time, philo->id);
        pthread_mutex_unlock(&philo->data->print_logs);
        pthread_mutex_lock(&philo->data->stop_simulation_mutex);
        philo->data->stop_simulation = 1;
        pthread_mutex_unlock(&philo->data->stop_simulation_mutex);
        return (1);
    }
    pthread_mutex_unlock(&philo->data->stop_simulation_mutex);
    return (0);
}

// void take_forks(t_philo *philo)
// {
//     int right;
//     int left;

//     if (philo->data->stop_simulation)
//         return;
//     left = philo->id - 1;
//     right = philo->id % philo->data->num_philosophers;
//     if (left < right)
//     {
//         pthread_mutex_lock(&philo->data->forks[left]);
//         log_message(philo, "has taken a fork");
//         pthread_mutex_lock(&philo->data->forks[right]);
//         log_message(philo, "has taken a fork");
//     }
//     else
//     {
//         pthread_mutex_lock(&philo->data->forks[right]);
//         log_message(philo, "has taken a fork");
//         pthread_mutex_lock(&philo->data->forks[left]);
//         log_message(philo, "has taken a fork");
//     }
// }
void take_forks(t_philo *philo)
{
    int left = philo->id - 1;
    int right = philo->id % philo->data->num_philosophers;

    // Verifique a condição de parada antes de pegar os garfos
    pthread_mutex_lock(&philo->data->stop_simulation_mutex);
    if (philo->data->stop_simulation)
    {
        pthread_mutex_unlock(&philo->data->stop_simulation_mutex);
        return;
    }
    pthread_mutex_unlock(&philo->data->stop_simulation_mutex);

    // Garanta que o garfo com o menor índice seja adquirido primeiro
    if (left < right)
    {
        pthread_mutex_lock(&philo->data->forks[left]);
        log_message(philo, "has taken a fork");

        pthread_mutex_lock(&philo->data->stop_simulation_mutex);
        if (philo->data->stop_simulation)
        {
            pthread_mutex_unlock(&philo->data->stop_simulation_mutex);
            pthread_mutex_unlock(&philo->data->forks[left]);
            return;
        }
        pthread_mutex_unlock(&philo->data->stop_simulation_mutex);

        pthread_mutex_lock(&philo->data->forks[right]);
        log_message(philo, "has taken a fork");
    }
    else
    {
        pthread_mutex_lock(&philo->data->forks[right]);
        log_message(philo, "has taken a fork");

        pthread_mutex_lock(&philo->data->stop_simulation_mutex);
        if (philo->data->stop_simulation)
        {
            pthread_mutex_unlock(&philo->data->stop_simulation_mutex);
            pthread_mutex_unlock(&philo->data->forks[right]);
            return;
        }
        pthread_mutex_unlock(&philo->data->stop_simulation_mutex);

        pthread_mutex_lock(&philo->data->forks[left]);
        log_message(philo, "has taken a fork");
    }
}

void    eat(t_philo *philo)
{
    if (philo->data->stop_simulation)
        return;
    pthread_mutex_lock(&philo->data->meal_sync);
    philo->last_meal_time = ft_current_time();
    pthread_mutex_unlock(&philo->data->meal_sync);
    log_message(philo, "is eating");
    precise_usleep(philo->data->time_to_eat);
    philo->eating++;
}

void put_down_forks(t_philo *philo)
{
    if (philo->data->stop_simulation)
        return;
    int left = philo->id - 1;
    int right = philo->id % philo->data->num_philosophers;

    pthread_mutex_unlock(&philo->data->forks[right]);
    pthread_mutex_unlock(&philo->data->forks[left]);
}

void    sleep_and_think(t_philo *philo)
{
    if (philo->data->stop_simulation)
    return;
    log_message(philo, "is sleeping");
    precise_usleep(philo->data->time_to_sleep);
    if (philo->data->stop_simulation)
        return;
    log_message(philo, "is thinking");
}