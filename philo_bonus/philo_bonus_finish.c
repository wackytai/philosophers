/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_finish.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 15:00:40 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/07/05 15:38:25 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_sem(t_data *data)
{
	if (sem_open(&data->write_s, 1))
		return (1);
	if (sem_open(&data->forks, data->n))
		return (1);
	if (sem_open(&data->last_meal_s, 1))
		return (1);
	return (0);
}

void	init_pid(t_data *data)
{
	int	i;

	i = -1;
	data->pid = (pid_t *)malloc(sizeof(pid_t) * data->n);
	if (!data->pid)
	{
		close_semaphores(data);
		free_all(data);
		exit(printf("Error allocating pids\n"));
	}
	while (++i < data->n)
		data->pid[i] = -1;
}

void	close_semaphores(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n)
		sem_close(&data->forks[i]);
	sem_close(data->write_s);
}

void	free_all(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n)
		sem_unlink(&data->forks[i]);
	sem_unlink(data->write_s);
	if (data->forks)
		free(data->forks);
	if (data->philo)
		free(data->philo);
	if (data->pid)
		free(data->pid);
}
