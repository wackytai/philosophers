/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 12:43:22 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/07/03 15:09:04 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6 || check_input(argc, argv, &data) < 0)
	{
		printf("Usage: ./philo n_philos t_die t_eat t_sleep\n");
		exit (1);
	}
	data.philo = (t_data *)malloc(sizeof(t_data) * data.n);
	if (!data.philo)
		exit(printf("Error allocating philosophers\n"));
	data.forks = (sem_t *)malloc(sizeof(sem_t) * data.n);
	if (!data.forks)
	{
		free(data.philo);
		exit(printf("Error allocating forks\n"));
	}
	if (fill_philo(&data))
		free_all(&data);
	return (0);
}


int	fill_philo(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n)
	{
		data->philo[i].data = data;
		data->philo[i].n_philo = i + 1;
	}
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
