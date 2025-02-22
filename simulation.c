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

void *one_philosopher_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;

    pthread_mutex_lock(&philo->data->forks[0]);
    log_message(philo, "take a fork");
    precise_usleep(philo->data->time_to_die, philo->data);
    log_message(philo, "died");
    pthread_mutex_unlock(&philo->data->forks[0]);
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
void *phil_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    while (1)
    {
        pthread_mutex_lock(&philo->data->stop_simulation_mutex);
        if (philo->data->stop_simulation)
        {
            pthread_mutex_unlock(&philo->data->stop_simulation_mutex);
            break;
        }
        pthread_mutex_unlock(&philo->data->stop_simulation_mutex);
        eat(philo);
        pthread_mutex_lock(&philo->data->stop_simulation_mutex);
        if (philo->data->stop_simulation) {
            pthread_mutex_unlock(&philo->data->stop_simulation_mutex);
            break;
        }
        pthread_mutex_unlock(&philo->data->stop_simulation_mutex);
        sleep_and_think(philo);
    }
    return (NULL);
}

static void start_simulate_bigger_one(t_data *data)
{
    int i;
    pthread_t hypervisor;

    if (!data || !data->philosophers)
        return;
    i = -1;
    pthread_create(&hypervisor, NULL, &supervisor, data);
    while (++i < data->num_philosophers)
    {
        pthread_create(&data->philosophers[i].thread, NULL,
            &phil_routine, &data->philosophers[i]);
    }
    
    i = -1;
    pthread_join(hypervisor, NULL);
    while (++i < data->num_philosophers)
        pthread_join(data->philosophers[i].thread, NULL);
}

void start_simulation(t_data *data)
{
    data->start_time = ft_current_time();
    if (data->num_philosophers < 2)
        start_simulation_when_one(data);
    else
        start_simulate_bigger_one(data);
}