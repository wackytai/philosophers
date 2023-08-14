/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_finish.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 15:00:40 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/08/14 09:19:44 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_sem(t_data *data)
{
	sem_unlink("forks");
	sem_unlink("write");
	sem_unlink("last_meal");
	data->forks = sem_open("forks", O_CREAT, 0644, data->n);
	data->write_s = sem_open("write", O_CREAT, 0644, 1);
	data->last_meal_s = sem_open("last_meal", O_CREAT, 0644, 1);
	if (data->forks == SEM_FAILED || data->write_s == SEM_FAILED
		|| data->last_meal_s == SEM_FAILED)
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
	sem_close(data->forks);
	sem_close(data->write_s);
	sem_close(data->last_meal_s);
}

void	free_all(t_data *data)
{
	sem_unlink("write");
	sem_unlink("last_meal");
	sem_unlink("forks");
	if (data->philo)
		free(data->philo);
	if (data->pid)
		free(data->pid);
}

void	finish_processes(t_data *data)
{
	int	i;
	int	j;
	int	status;

	i = -1;
	while (++i < data->n)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			j = -1;
			while (++j < data->n)
				kill(data->pid[j], SIGTERM);
			break ;
		}
	}
	return ;
}
