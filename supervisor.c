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
    long time_since_last_meal;
    pthread_mutex_lock(&data->stop_simulation_mutex);
        if (data->stop_simulation)
        {
            pthread_mutex_unlock(&data->stop_simulation_mutex);
            return (NULL);
        }
    pthread_mutex_unlock(&data->stop_simulation_mutex);
    while (1)
    {
        i = -1;
        while (++i < data->num_philosophers)
        {
            pthread_mutex_lock(&data->meal_sync);
            time_since_last_meal = ft_current_time() - data->philosophers[i].last_meal_time;
            if (time_since_last_meal >= data->time_to_die)
            {
                pthread_mutex_lock(&data->print_logs);
                printf("%ld %d died\n", ft_current_time() - data->start_time, data->philosophers[i].id);
                pthread_mutex_unlock(&data->print_logs);

                pthread_mutex_lock(&data->stop_simulation_mutex);
                data->stop_simulation = 1;
                pthread_mutex_unlock(&data->stop_simulation_mutex);

                pthread_mutex_unlock(&data->meal_sync);
                return (NULL);
            }
            pthread_mutex_unlock(&data->meal_sync);
        }
        usleep(5000);
    }
    return (NULL);
}