/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 14:13:32 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/06/22 14:54:26 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_input(char **argv, int argc, t_philo *philos)
{
	int	i;
	int	res;

	i = 0;
	while (++i < argc)
	{
		res = ft_atoi(argv[i]);
		if (res <= 0)
			return (-1);
		if (i == 1)
			philos->n_philos = res;
		if (i == 2)
			philos->t_die;
		if (i == 3)
			philos->t_eat;
		if (i == 4)
			philos->t_sleep;
		if (i == 5)
			philos->n_meals;
	}
	philos->n_forks = philos->n_philos;
	return (0);
}

int	ft_atoi(char *str)
{
	long long	res;
	int			i;

	res = 0;
	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		return (-1);
	if (str[i] == '+')
		i++;
	while (str[i] >= 48 && str[i] <= 57)
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	if (res > INT_MAX || res < INT_MIN)
		return (-1);
	return (res);
}
