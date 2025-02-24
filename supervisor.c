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
    long timestamp;
    long current_time;
    long last_meal;
    int died;

    died = 0;
    pthread_mutex_lock(&data->meal_sync);
    current_time = ft_current_time();
    last_meal = data->philosophers[i].last_meal_time;
    died = (current_time - last_meal) > data->time_to_die;
    pthread_mutex_unlock(&data->meal_sync);

    if (died)
    {
        pthread_mutex_lock(&data->stop_simulation_mutex);
        if (!data->stop_simulation)
        {
            data->stop_simulation = 1;
            pthread_mutex_lock(&data->print_logs);
            timestamp = current_time - data->start_time;
            printf("%ldms %d died\n", timestamp, i + 1);
            pthread_mutex_unlock(&data->print_logs);
        }
        pthread_mutex_unlock(&data->stop_simulation_mutex);
    }
}

int check_all_ate_enough(t_data *data) {
    int all_ate_enough;
    int i;

    i = 0;
    all_ate_enough = 1;
    while (i < data->num_philosophers)
    {
        pthread_mutex_lock(&data->meal_sync);
        if (data->philosophers[i].eating < data->must_eat_count)
        {
            all_ate_enough = 0;
            pthread_mutex_unlock(&data->meal_sync);
            break;
        }
        pthread_mutex_unlock(&data->meal_sync);
        i++;
    }
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
            check_philosopher(data, i);
        if (data->must_eat_count != -1 && check_all_ate_enough(data)) 
        {
            pthread_mutex_lock(&data->stop_simulation_mutex);
            data->stop_simulation = 1;
            pthread_mutex_unlock(&data->stop_simulation_mutex);
            break;
        }
        usleep(100);
    }
    return (NULL);
}