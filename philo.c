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



int main(int ac, char **av)
{
    t_data  *data;

    if (ac < 5 || ac > 6)
    {
        printf("%sError[N01]: Wrong number of arguments\n", ERROR);
        return (-1);
    }
    data = malloc(sizeof(t_data));
    if (!data)
        return (-1);
    if (ft_checker_input(av) == -42)
    {
        printf("%sError[P01]: invalid parameters\n", ERROR);
        free(data);
        return (-1);
    }
    if (ft_parse_args(data, ac, av))
    {
        printf("%sError[P02]: during parsing\n", ERROR);
        free(data);
        return (-1);
    }
    if (ft_init_data(data))
    {
        printf("%sError[P03]: init philo\n", ERROR);
        free(data);
        return (-1);
    }
    start_simulation(data);
    cleanup(data);
    return (0);
}
