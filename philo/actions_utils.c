/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 11:21:20 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/07/04 13:26:59 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_meal_m);
	if ((get_time() - philo->last_meal) >= philo->attr->t_die)
	{
		pthread_mutex_lock(&philo->attr->flag_m);
		philo->attr->flag = 1;
		pthread_mutex_unlock(&philo->attr->flag_m);
		print_action(philo, "died", 1);
		pthread_mutex_unlock(&philo->last_meal_m);
		return (1);
	}
	pthread_mutex_unlock(&philo->last_meal_m);
	return (0);
}

void	one_philosopher(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_1);
	print_action(philo, "has taken a fork", 0);
	usleep(philo->attr->t_die * 1000);
	print_action(philo, "died", 1);
	pthread_mutex_unlock(philo->fork_1);
	exit(0);
}

int	check_flag(t_attr *data)
{
	pthread_mutex_lock(&data->flag_m);
	if (data->flag)
	{
		pthread_mutex_unlock(&data->flag_m);
		return (1);
	}
	pthread_mutex_unlock(&data->flag_m);
	return (0);
}

void	routine_check(t_attr *data)
{
	int	i;
	int	count;

	sync_time(data);
	while (1)
	{
		i = -1;
		count = 1;
		while (++i < data->n)
		{
			if (check_death(&data->philos[i]))
				return ;
			if (data->max_meal)
				count = update_count(&data->philos[i]);
		}
		if (data->max_meal && count)
		{
			pthread_mutex_lock(&data->flag_m);
			data->flag = 1;
			pthread_mutex_unlock(&data->flag_m);
			break ;
		}
		usleep(1000);
	}
}

int	update_count(t_philo *philo)
{
	pthread_mutex_lock(&philo->n_meal_m);
	if (philo->meal < philo->attr->max_meal)
	{
		pthread_mutex_unlock(&philo->n_meal_m);
		return (0);
	}
	pthread_mutex_unlock(&philo->n_meal_m);
	return (1);
}
