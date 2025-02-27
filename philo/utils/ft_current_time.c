/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_current_time.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmacau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 08:53:02 by fmacau            #+#    #+#             */
/*   Updated: 2025/02/27 11:07:09 by fmacau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

time_t	ft_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	precise_usleep(long usec, t_data *data)
{
	long	start_time;

	start_time = ft_current_time() + usec;
	while (ft_current_time() < start_time)
	{
		usleep(usec / 10);
		if (get_simulation_status(data))
			break ;
	}
}
