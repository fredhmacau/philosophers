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

#include "./includes/philo.h"

void print_error(const char *code, const char *msg)
{
    printf("%sError[%s]: %s\n", ERROR, code, msg);
}

void free_data(t_data *data)
{
    free(data);
}

int initialize_data(t_data *data, int ac, char **av)
{
    if (ft_checker_input(av) == -42)
    {
        print_error("P01", "invalid parameters");
        return (-1);
    }
    if (ft_parse_args(data, ac, av))
    {
        print_error("P02", "during parsing");
        return (-1);
    }
    if (ft_init_data(data))
    {
        print_error("P03", "init philo");
        return (-1);
    }
    return (0);
}

int main(int ac, char **av)
{
    t_data *data;

    if (ac < 5 || ac > 6)
    {
        print_error("N01", "Wrong number of arguments");
        return (-1);
    }
    data = malloc(sizeof(t_data));
    if (!data)
        return (-1);
    if (initialize_data(data, ac, av) == -1)
    {
        free_data(data);
        return (-1);
    }
    start_simulation(data);
    cleanup(data);
    return (0);
}