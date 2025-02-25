/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmacau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 08:24:55 by fmacau            #+#    #+#             */
/*   Updated: 2025/02/12 08:24:56 by fmacau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

int ft_init_data(t_data *data)
{
    int i;
    
    data->philosophers = malloc(data->num_philosophers * sizeof(t_philo));
    data->forks = malloc(data->num_philosophers * sizeof(pthread_mutex_t));
    if (!data->philosophers || !data->forks)
        return (1);
    i = -1;
    while (++i < data->num_philosophers)
        pthread_mutex_init(&data->forks[i], NULL);
    
    pthread_mutex_init(&data->print_logs, NULL);
    pthread_mutex_init(&data->stop_simulation_mutex, NULL);
    i = -1;
    data->start_time = ft_current_time();
    while (++i < data->num_philosophers)
    {
        data->philosophers[i].id = i;
        data->philosophers[i].eating = 0;
        data->philosophers[i].last_meal_time = data->start_time;
        data->philosophers[i].data = data;
        pthread_mutex_init(&data->philosophers[i].meal_mutex, NULL);
    }
    data->stop_simulation = 0;
    data->num_philo_who_ate = 0;
    return (0);
}
