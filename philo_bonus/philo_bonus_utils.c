/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:04:27 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/07/03 13:34:13 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_input(int argc, char **argv, t_data *data)
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
			data->n = res;
		else if (i == 2)
			data->t_die = res * 1000;
		else if (i == 3)
			data->t_eat = res * 1000;
		else if (i == 4)
			data->t_sleep = res * 1000;
		else if (i == 5)
			data->max_meal = res;
	}
	if (argc == 5)
		data->max_meal = 0;
	data->t_die2 = data->t_die2 / 1000;
	return (0);
}

int	ft_atoi(char *str)
{
	int			i;
	long long	res;

	i = 0;
	res = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+')
		i++;
	if (str[i] == '-')
		return (-1);
	while (str[i] > 47 && str[i] < 58)
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	if (res < INT_MIN || res > INT_MAX)
		return (-1);
	return (res);
}
