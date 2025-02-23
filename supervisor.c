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

    if (ft_current_time() - data->philosophers[i].last_meal_time > data->time_to_die)
    {
        log_message(&data->philosophers[i], "died");
        pthread_mutex_lock(&data->stop_simulation_mutex);
        data->stop_simulation = 1;
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
        if (data->philosophers[i].eating < data->must_eat_count)
        {
            all_ate_enough = 0;
            break;
        }
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
        {
            check_philosopher(data, i);
            if (data->stop_simulation) {
                return (NULL);
            }
        }
        if (data->must_eat_count != -1 && check_all_ate_enough(data)) 
        {
            pthread_mutex_lock(&data->stop_simulation_mutex);
            data->stop_simulation = 1;
            pthread_mutex_unlock(&data->stop_simulation_mutex);
            return (NULL);
        }
    }
    return (NULL);
}