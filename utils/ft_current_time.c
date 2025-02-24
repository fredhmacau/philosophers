/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_current_time.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmacau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 08:53:02 by fmacau            #+#    #+#             */
/*   Updated: 2025/02/12 08:53:04 by fmacau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long ft_current_time(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

void precise_usleep(long usec, t_data *data)
{

    long start_time;
    start_time = ft_current_time() + usec;
    while (ft_current_time() < start_time)
    {
        usleep(100);
        pthread_mutex_lock(&data->stop_simulation_mutex);
        if (data->stop_simulation) {
            pthread_mutex_unlock(&data->stop_simulation_mutex);
            break;
        }
        pthread_mutex_unlock(&data->stop_simulation_mutex);
        
    }

}