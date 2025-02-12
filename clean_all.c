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

    i = -1;
    while (i++ < data->num_philosophers)
        pthread_mutex_destroy(&data->forks[i]);
}

void cleanup(t_data *data)
{
    if (!data)
        return ;
    if (data->forks)
    {
        destroy_forks(data);
        free(data->forks);
        data->forks = NULL;
    }
    if (pthread_mutex_destroy(&data->print_logs) != 0)
        return ;
    if (pthread_mutex_destroy(&data->meal_sync) != 0)
        return ;
    
    if (data->philosophers)
    {
        free(data->philosophers);
        data->philosophers = NULL;
    }
    data->num_philosophers = 0;
}