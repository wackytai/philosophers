/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 10:04:39 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/06/29 14:13:32 by tlemos-m         ###   ########.fr       */
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

void	*routine(void *philos)
{
	t_philo	*philo;

	philo = (t_philo *)philos;
	/* loop while nobody died
	put everybody to think?
	try to acquire forks
	eat()
	sleep()
	think() */
	while (!check_death(philo->attr))
	{
		think(philo);
		eat(philo);
		ft_sleep(philo);
	}
	return (0);
}

void	eat(t_philo *philo)
{
	int	time;

	time = philo->attr->t_eat * 1000;
	pthread_mutex_lock(philo->fork_1);
	print_action(philo, -1);
	pthread_mutex_lock(philo->fork_2);
	print_action(philo, -1);
	pthread_mutex_lock(philo->last_meal_m);
	philo->last_meal = get_time();
	pthread_mutex_unlock(philo->last_meal_m);
	print_action(philo, 0);
	usleep(time);
	pthread_mutex_lock(philo->n_meal_m);
	philo->meal += 1;
	pthread_mutex_unlock(philo->n_meal_m);
	pthread_mutex_unlock(philo->fork_2);
	pthread_mutex_unlock(philo->fork_1);
	return ;
}

void	think(t_philo *philo)
{
	print_action(philo, 1);
	return ;
}

void	ft_sleep(t_philo *philo)
{
	int	time;

	time = philo->attr->t_sleep * 1000;
	print_action(philo, 2);
	usleep(time);
	return ;
}
