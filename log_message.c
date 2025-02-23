/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_message.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmacau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:50:54 by fmacau            #+#    #+#             */
/*   Updated: 2025/02/12 10:50:56 by fmacau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

void    log_message(t_philo *philo, char *action)
{
    long timestamp;
    if (!philo || !action)
        return ;
    if (philo->data->stop_simulation) {
        pthread_mutex_unlock(&philo->data->stop_simulation_mutex);
        return;
    }
    pthread_mutex_lock(&philo->data->print_logs);
    timestamp = ft_current_time() - philo->data->start_time;
    printf("%ldms %d %s\n", timestamp, philo->id + 1, action);
    pthread_mutex_unlock(&philo->data->print_logs);
}