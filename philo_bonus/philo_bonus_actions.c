/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_actions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 14:34:44 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/07/05 15:01:13 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	one_philosopher(t_philo *philo)
{
	sem_wait(philo->data->forks);
	print_action(philo, "has taken a fork", 0);
	usleep(philo->data->t_eat);
	sem_post(philo->data->forks);
	print_action(philo, "died", 1);
	philo->status = 1;
	exit(philo->status);
}

void	eat(t_philo *philo)
{
	sem_wait(philo->data->forks);
	print_action(philo, "has taken a fork", 0);
	sem_wait(philo->data->forks);
	print_action(philo, "has taken a fork", 0);
	sem_wait(philo->data->last_meal_s);
	philo->last_meal = get_time();
	sem_post(philo->data->last_meal_s);
	print_action(philo, "is eating", 0);
	usleep(philo->data->t_eat);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
	philo->meal++;
	print_action(philo, "is sleeping", 0);
	usleep(philo->data->t_sleep);
	return ;
}
