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
    (void) av;
    if (ac < 5 || ac > 6)
    {
        printf("Error: Wrong number of arguments\n");
        return (-1);
    }
    return (0);
}