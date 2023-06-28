/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 10:04:39 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/06/28 10:52:49 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	assign_forks(t_attr *data)
{
	int	i;

	i = -1;
	while (++i < data->n)
	{
		if (i % 2)
		{
			data->philos[i].fork_1 = &data->forks[i];
			data->philos[i].fork_2 = &data->forks[(i + 1) % data->n];
		}
		else
		{
			data->philos[i].fork_1 = &data->forks[(i + 1) % data->n];
			data->philos[i].fork_2 = &data->forks[i];
		}
	}
}

void	*routine(void *data)
{
	/* put everybody to think?
	check if next and previous are not in hungry mode and enters hungry mode 
		aka try to acquire forks
	eat()
	sleep()
	think() */
	return ;
}

void	eat(t_attr *data)
{
	int	time;

	time = data->t_eat * 1000;
	/* get forks
	pthread_mutex_lock(data->philos[data->philos->n_philo - 1].fork_1)
	pthread_mutex_lock(data->philos[data->philos->n_philo - 1].fork_2) */
	print_action(data, 0);
	usleep(time);
	/* put forks down
	pthread_mutex_unlock(data->philos[data->philos->n_philo - 1].fork_2)
	pthread_mutex_unlock(data->philos[data->philos->n_philo - 1].fork_1) */
	data->philos[data->philos->n_philo - 1].last_meal = get_time();
	return ;
}

void	think(t_attr *data)
{
	print_action(data, 1);
	return ;
}

void	sleep(t_attr *data)
{
	int	time;

	time = data->t_sleep * 1000;
	print_action(data, 2);
	usleep(time);
	return ;
}
