/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmacau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 01:10:44 by fmacau            #+#    #+#             */
/*   Updated: 2025/02/25 01:10:50 by fmacau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/philo.h"

int get_simulation_status(t_data *data)
{
    int status;

    pthread_mutex_lock(&data->stop_simulation_mutex);
    status = data->stop_simulation;
    pthread_mutex_unlock(&data->stop_simulation_mutex);
    return status;
}

void set_simulation_status(t_data *data, int status) 
{
    pthread_mutex_lock(&data->stop_simulation_mutex);
    data->stop_simulation = status;
    pthread_mutex_unlock(&data->stop_simulation_mutex);
}