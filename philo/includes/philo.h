/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmacau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:31:51 by fmacau            #+#    #+#             */
/*   Updated: 2025/02/27 17:38:17 by fmacau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/types.h>
# include <sys/time.h>
# define ERROR "\x1b[31m"
# define EATING "\x1b[32m"
# define SLEEPING "\x1b[35m"
# define FORK "\x1b[34m"
# define THINKING "\x1b[33m"
# define DIE "\x1b[31m"

typedef struct s_philo
{
	struct s_data	*data;
	pthread_t		thread;
	int				id;
	int				eating;
	long			last_meal_time;
	pthread_mutex_t	meal_mutex;
}	t_philo;

typedef struct s_data
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	stop_simulation_mutex;
	pthread_mutex_t	print_logs;
	pthread_t		supervisor;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			start_time;
	int				num_philosophers;
	int				must_eat_count;
	int				stop_simulation;
	t_philo			*philosophers;
}	t_data;

time_t	ft_current_time(void);
long	ft_atoi(char *str);
void	set_simulation_status(t_data *data, int status);
void	log_message(t_philo *philo, char *action, char *status);
void	sleep_and_think(t_philo *philo);
void	eat(t_philo *philo);
void	start_simulation(t_data *data);
void	cleanup(t_data *data);
void	precise_usleep(long usec, t_data *data);
void	*supervisor(void *arg);
int		ft_isdigit(int c);
int		ft_checker_input(char **av);
int		ft_parse_args(t_data *data, int ac, char **av);
int		ft_init_data(t_data *data);
int		get_simulation_status(t_data *data);
#endif
