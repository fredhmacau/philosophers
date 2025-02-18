/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmacau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:07:08 by fmacau            #+#    #+#             */
/*   Updated: 2025/01/28 16:31:06 by fmacau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"


void *supervisor(void *arg)
{   
    t_data  *data = (t_data *)arg;
    int i;
    long time_since_last_meal;

    while (1)
    {
        i = -1;
        while (++i < data->num_philosophers)
        {
            pthread_mutex_lock(&data->meal_sync);
            time_since_last_meal = ft_current_time() - data->philosophers[i].last_meal_time;
            if (time_since_last_meal >= data->time_to_die)
            {
                printf("%ld %d died\n", ft_current_time() - data->start_time, data->philosophers[i].id);
                pthread_mutex_lock(&data->stop_simulation_mutex);
                data->stop_simulation = 1;
                pthread_mutex_unlock(&data->stop_simulation_mutex);
                pthread_mutex_unlock(&data->meal_sync);
                return (NULL);
            }
            pthread_mutex_unlock(&data->meal_sync);
        }
        usleep(1000);
    }
    return (NULL);
}
int main(int ac, char **av)
{
    t_data  data;

    if (ac < 5 || ac > 6)
    {
        printf("%sError[N01]: Wrong number of arguments\n", ERROR);
        return (-1);
    }
    if (ft_checker_input(av) == -42)
    {
        printf("%sError[P01]: invalid parameters\n", ERROR);
        return (-1);
    }
    if (ft_parse_args(&data, ac, av))
    {
        printf("%sError[P02]: during parsing\n", ERROR);
        return (-1);
    }
    if (ft_init_data(&data))
    {
        printf("%sError[P03]: init philo\n", ERROR);
        return (-1);
    }
    pthread_create(&data.supervisor, NULL, &supervisor, &data);
    start_simulation(&data);
    pthread_join(data.supervisor, NULL);
    cleanup(&data);
    return (0);
}
