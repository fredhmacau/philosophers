/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmacau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 09:05:51 by fmacau            #+#    #+#             */
/*   Updated: 2025/02/12 09:05:52 by fmacau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

void    *one_philosopher_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;

    pthread_mutex_lock(&philo->data->print_logs);
    printf("%ld %d take a fork\n", ft_current_time() - philo->data->start_time, philo->id);
    pthread_mutex_unlock(&philo->data->print_logs);
    precise_usleep(philo->data->time_to_die);
    pthread_mutex_lock(&philo->data->print_logs);
    printf("%ld %d died\n", ft_current_time() - philo->data->start_time, philo->id);
    pthread_mutex_unlock(&philo->data->print_logs);
    return (NULL);
}

static void start_simulation_when_one(t_data *data)
{
   if (!data->philosophers)
        return ;
   pthread_create(&data->philosophers[0].thread, NULL,
                  &one_philosopher_routine, &data->philosophers[0]);
   pthread_join(data->philosophers[0].thread, NULL);
}

void    *phil_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;

    while (1)
    {
        pthread_mutex_lock(&philo->data->stop_simulation_mutex);
        if (philo->data->stop_simulation)
        {
            pthread_mutex_unlock(&philo->data->stop_simulation_mutex);
            break;
        }
        pthread_mutex_unlock(&philo->data->stop_simulation_mutex);
        take_forks(philo);
        eat(philo);
        put_down_forks(philo);
        sleep_and_think(philo);
        if (philo->data->must_eat_count != -1 &&
            philo->eating >= philo->data->must_eat_count)
        {
            pthread_mutex_lock(&philo->data->meal_sync);
            philo->data->num_philo_who_ate++;
            pthread_mutex_unlock(&philo->data->meal_sync);
            if (philo->data->num_philo_who_ate == philo->data->must_eat_count)
            {
                pthread_mutex_lock(&philo->data->stop_simulation_mutex);
                philo->data->stop_simulation = 1;
                pthread_mutex_unlock(&philo->data->stop_simulation_mutex);
            }
        }
    }
    return (NULL);
}

static void start_simulate_bigger_one(t_data *data)
{
    int i;

    if (!data || !data->philosophers)
        return;
    i = -1;
    while (++i < data->num_philosophers)
        pthread_create(&data->philosophers[i].thread, NULL,
                       &phil_routine, &data->philosophers[i]);
    
    i = -1;
    while (++i < data->num_philosophers)
        pthread_join(data->philosophers[i].thread, NULL);
}

void    start_simulation(t_data *data)
{
    if (data->num_philosophers < 2)
        start_simulation_when_one(data);
    else
        start_simulate_bigger_one(data);
}
