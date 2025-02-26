/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmacau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 07:57:40 by fmacau            #+#    #+#             */
/*   Updated: 2025/02/19 07:57:47 by fmacau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

int check_philosopher(t_data *data, int i) {
    long current_time;
    long last_meal;
    int died;

    died = 0;
    current_time = ft_current_time();
    last_meal = data->philosophers[i].last_meal_time;
    died = (current_time - last_meal) > (data->time_to_die + 3);
    if (died && !get_simulation_status(data))
    {
        set_simulation_status(data, 1);
        pthread_mutex_lock(&data->print_logs);
        printf("%ldms %d died\n", (current_time - data->start_time), i + 1);
        pthread_mutex_unlock(&data->print_logs);
        return 1;
    }
    return 0;
}

int check_all_ate_enough(t_data *data) {
    int all_ate_enough;
    int i;

    i = 0;
    all_ate_enough = 1;
    while (i < data->num_philosophers)
    {
        if (data->philosophers[i].eating < data->must_eat_count)
        {
            all_ate_enough = 0;
            break;
        }
        i++;
    }
    return all_ate_enough;
}
void lock_all_meal_mutexes(t_data *data)
{
    int i;

    i = -1;
    while (++i < data->num_philosophers)
        pthread_mutex_lock(&data->philosophers[i].meal_mutex);
}

void unlock_all_meal_mutexes(t_data *data)
{
    int i;

    i = -1;
    while (++i < data->num_philosophers)
        pthread_mutex_unlock(&data->philosophers[i].meal_mutex);
}
void *supervisor(void *arg)
{
    t_data *data;
    int death_detected;
    int i;

    data = (t_data *)arg;
    while (!get_simulation_status(data))
    {
        lock_all_meal_mutexes(data);
        death_detected = 0;
        i = -1;
        while (++i < data->num_philosophers)
        {
            if (check_philosopher(data, i))
            {
                death_detected = 1;
                break;
            }
        }
        if (!death_detected && (data->must_eat_count != -1 && check_all_ate_enough(data)))
            set_simulation_status(data, 1);
        unlock_all_meal_mutexes(data);
        usleep(500);
    }
    return (NULL);
}