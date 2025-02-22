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

void *supervisor(void *arg)
{
    t_data *data = (t_data *)arg;
    int i;
    int all_ate_enough;

    while (!data->stop_simulation) {
        i = -1;
        while (++i < data->num_philosophers) {
            pthread_mutex_lock(&data->meal_sync);
            long time_since_last_meal = ft_current_time() - data->philosophers[i].last_meal_time;
            if (time_since_last_meal >= data->time_to_die) {
                log_message(&data->philosophers[i], "died");
                pthread_mutex_lock(&data->stop_simulation_mutex);
                data->stop_simulation = 1;
                pthread_mutex_unlock(&data->stop_simulation_mutex);
                pthread_mutex_unlock(&data->meal_sync);
                return (NULL);
            }
            pthread_mutex_unlock(&data->meal_sync);
        }

        if (data->must_eat_count != -1) {
            pthread_mutex_lock(&data->meal_sync);
            all_ate_enough = 1;
            for (i = 0; i < data->num_philosophers; i++) {
                if (data->philosophers[i].eating < data->must_eat_count) {
                    all_ate_enough = 0;
                    break;
                }
            }
            pthread_mutex_unlock(&data->meal_sync);

            if (all_ate_enough) {
                pthread_mutex_lock(&data->stop_simulation_mutex);
                data->stop_simulation = 1;
                pthread_mutex_unlock(&data->stop_simulation_mutex);
                return (NULL);
            }
        }
        usleep(100);
    }
    return (NULL);
}