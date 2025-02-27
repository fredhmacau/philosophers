/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_message.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmacau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:50:54 by fmacau            #+#    #+#             */
/*   Updated: 2025/02/27 10:46:27 by fmacau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

void	log_message(t_philo *philo, char *action, char *status)
{
	long	timestamp;

	if (!philo || !action)
		return ;
	if (get_simulation_status(philo->data))
		return ;
	pthread_mutex_lock(&philo->data->print_logs);
	timestamp = ft_current_time() - philo->data->start_time;
	printf("%s%ldms %d %s\n", status, timestamp, philo->id + 1, action);
	pthread_mutex_unlock(&philo->data->print_logs);
}
