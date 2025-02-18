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
    timestamp = ft_current_time() - philo->data->start_time;
    pthread_mutex_lock(&philo->data->print_logs);
    printf("%ld %d %s\n", timestamp, philo->id, action);
    pthread_mutex_unlock(&philo->data->print_logs);
}