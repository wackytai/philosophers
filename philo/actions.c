/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 10:04:39 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/07/05 09:49:46 by tlemos-m         ###   ########.fr       */
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
	sync_time(philo->attr);
	if (philo->attr->n == 1)
		one_philosopher(philo);
	if (philo->n_philo % 2)
		usleep(200000);
	while (!check_flag(philo->attr))
	{
		eat(philo);
		print_action(philo, "is thinking", 0);
	}
	return (0);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_1);
	print_action(philo, "has taken a fork", 0);
	pthread_mutex_lock(philo->fork_2);
	print_action(philo, "has taken a fork", 0);
	pthread_mutex_lock(&philo->last_meal_m);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->last_meal_m);
	print_action(philo, "is eating", 0);
	usleep(philo->attr->t_eat);
	pthread_mutex_unlock(philo->fork_1);
	pthread_mutex_unlock(philo->fork_2);
	pthread_mutex_lock(&philo->n_meal_m);
	philo->meal += 1;
	pthread_mutex_unlock(&philo->n_meal_m);
	print_action(philo, "is sleeping", 0);
	usleep(philo->attr->t_sleep);
	return ;
}
