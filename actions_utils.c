/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 11:21:20 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/06/29 15:13:45 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_attr *data)
{
	int	i;

	i = -1;
	while (++i < data->n)
	{
		pthread_mutex_lock(data->philos[i].last_meal_m);
		if ((get_time() - data->philos[i].last_meal) >= data->t_die
			|| data->philos[i].meal >= data->max_meal)
		{
			pthread_mutex_lock(&data->flag_m);
			data->flag = 1;
			pthread_mutex_unlock(&data->flag_m);
			print_action(&data->philos[i], 3);
			return (1);
		}
		pthread_mutex_unlock(data->philos[i].last_meal_m);
	}
	return (0);
}
