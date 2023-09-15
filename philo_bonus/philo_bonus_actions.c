/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_actions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 14:34:44 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/09/15 12:15:02 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eat(t_philo *philo)
{
	sem_wait(philo->data->forks);
	print_action(philo, "has taken a fork");
	sem_wait(philo->data->forks);
	print_action(philo, "has taken a fork");
	sem_wait(philo->data->last_meal_s);
	if (philo->data->t_die2 > (get_time() - philo->last_meal))
		philo->last_meal = get_time();
	else
		return ;
	sem_post(philo->data->last_meal_s);
	print_action(philo, "is eating");
	usleep(philo->data->t_eat);
	philo->meal++;
	sem_post(philo->data->forks);
	print_action(philo, "has released a fork");
	sem_post(philo->data->forks);
	print_action(philo, "has released a fork");
	if (philo->meal == philo->data->max_meal)
		exit (0);
	print_action(philo, "is sleeping");
	usleep(philo->data->t_sleep);
	return ;
}

void	think(t_philo *philo)
{
	time_t	time_to_think;

	sem_wait(philo->data->last_meal_s);
	time_to_think = (philo->data->t_die2
			- (get_time() - philo->last_meal)
			- philo->data->t_eat) / 2;
	sem_post(philo->data->last_meal_s);
	if (time_to_think < 1)
		time_to_think = 1;
	if (time_to_think > 600)
		time_to_think = 200;
	print_action(philo, "is thinking");
	usleep(time_to_think);
}
