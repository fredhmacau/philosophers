/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmacau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 07:57:40 by fmacau            #+#    #+#             */
/*   Updated: 2025/02/19 07:57:47 by fmacau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

void check_philosopher(t_data *data, int i) {
    long time_since_last_meal;

    pthread_mutex_lock(&data->meal_sync);
    time_since_last_meal = ft_current_time() - data->philosophers[i].last_meal_time;
    if (time_since_last_meal >= data->time_to_die) {
        log_message(&data->philosophers[i], "died");
        pthread_mutex_lock(&data->stop_simulation_mutex);
        data->stop_simulation = 1;
        pthread_mutex_unlock(&data->stop_simulation_mutex);
    }
    pthread_mutex_unlock(&data->meal_sync);
}

int check_all_ate_enough(t_data *data) {
    int all_ate_enough;
    int i;

    i = 0;
    all_ate_enough = 1;

    pthread_mutex_lock(&data->meal_sync);
    while (i < data->num_philosophers)
    {
        if (data->philosophers[i].eating < data->must_eat_count)
        {
            all_ate_enough = 0;
            break;
        }
        i++;
    }
    pthread_mutex_unlock(&data->meal_sync);
    return all_ate_enough;
}

void *supervisor(void *arg) {
    t_data *data;
    int i;

    data = (t_data *)arg;
    while (!data->stop_simulation)
    {
        i = -1;
        while (++i < data->num_philosophers)
        {
            check_philosopher(data, i);
            pthread_mutex_lock(&data->stop_simulation_mutex);
            if (data->stop_simulation) {
                pthread_mutex_unlock(&data->stop_simulation_mutex);
                return (NULL);
            }
            pthread_mutex_unlock(&data->stop_simulation_mutex);
        }
        if (data->must_eat_count != -1 && check_all_ate_enough(data)) 
        {
            pthread_mutex_lock(&data->stop_simulation_mutex);
            data->stop_simulation = 1;
            pthread_mutex_unlock(&data->stop_simulation_mutex);
            return (NULL);
        }
        usleep(1000);
    }
    return (NULL);
}