/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 12:43:22 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/07/05 13:37:04 by tlemos-m         ###   ########.fr       */
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
	if (create_philos(&data))
		free_all(&data);
	return (0);
}


int	create_philos(t_data *data)
{
	int	i;

	i = -1;
	if (init_sem(data))
		return (1);
	init_pid(data);
	while (++i < data->n)
	{
		data->pid[i] = fork();
		if (data->pid[i] < 0)
			return (printf("Error forking\n"));
		if (!data->pid[i])
		{
			data->philo[i].tid = -1;
			data->philo[i].meal = 0;
			data->philo[i].data = data;
			data->philo[i].n_philo = i + 1;
			data->philo[i].last_meal = data->t_start;
			handle_philo(&data->philo[i]);
		}
	}
	if (waitpid(-1, 1, 0))
		kill(0, 1);
}

void	handle_philo(t_philo *philo)
{
	philo->status = 0;
	if (pthread_create(philo->tid, 0, routine, philo))
	{
		close_semaphores(philo->data);
		free_all(philo->data);
		exit (3);
	}
	if (philo->data->n > 1)
	{
		routine_check(philo);
		pthread_detach(philo->tid);
		exit(philo->status);
	}
}

void	*routine(void *philo)
{
	
}

void	routine_check(t_philo *philo)
{
	
}
