/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmacau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 16:50:15 by fmacau            #+#    #+#             */
/*   Updated: 2025/02/27 10:43:08 by fmacau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

int	ft_checker_args(char *av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (av[i] == ' ')
			i++;
		if (!ft_isdigit(av[i]))
			return (-42);
		i++;
	}
	return (1);
}

int	ft_other_analyzes(char *av)
{
	if (ft_atoi(av) <= 0)
		return (-42);
	return (1);
}

int	ft_checker_input(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (ft_checker_args(av[i]) == -42)
			return (-42);
		i++;
	}
	if (!(ft_atoi(av[1]) >= 1 && ft_atoi(av[1]) <= 200))
		return (-42);
	i = 2;
	while (av[i])
	{
		if (ft_other_analyzes(av[i]) == -42)
			return (-42);
		i++;
	}
	return (1);
}
