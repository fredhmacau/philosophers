/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmacau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:10:16 by fmacau            #+#    #+#             */
/*   Updated: 2025/02/12 12:10:18 by fmacau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./includes/philo.h"


static void destroy_forks(t_data *data)
{
    int i;

    i = 0;
    while (i < data->num_philosophers)
    {
        pthread_mutex_destroy(&data->forks[i]);
        i++;
    }
}

void cleanup(t_data *data)
{
    if (!data)
        return ;
    if (data->philosophers != NULL) {
        free(data->philosophers);
    }
    if (data->forks)
    {
        destroy_forks(data);
        free(data->forks);
        data->forks = NULL;
    }
    pthread_mutex_destroy(&data->print_logs);
    pthread_mutex_destroy(&data->meal_sync);
    pthread_mutex_destroy(&data->stop_simulation_mutex);
    pthread_mutex_destroy(&data->forks_lock);
    data->num_philosophers = 0;
    free(data);
}