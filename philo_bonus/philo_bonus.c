/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 12:43:22 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/07/06 09:14:36 by tlemos-m         ###   ########.fr       */
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
	data.philo = (t_philo *)malloc(sizeof(t_philo) * data.n);
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
			handle_philo(&data->philo[i]);
		}
	}
	finish_processes(data);
	return (0);
}

int	handle_philo(t_philo *philo)
{
	philo->data->t_start = get_time() + (philo->data->n * 2);
	philo->last_meal = philo->data->t_start;
	if (pthread_create(&philo->tid, 0, routine, philo))
	{
		close_semaphores(philo->data);
		free_all(philo->data);
		return (1);
	}
	if (philo->data->n > 1)
	{
		routine_check(philo);
		pthread_detach(philo->tid);
		return (0);
	}
	pthread_join(philo->tid, 0);
	return (0);
}

void	*routine(void *philos)
{
	t_philo	*philo;

	philo = (t_philo *)philos;
	sync_time(philo->data);
	if (philo->data->n == 1)
		one_philosopher(philo);
	if (philo->n_philo % 2)
		usleep(200000);
	while (!philo->data->flag)
	{
		eat(philo);
		print_action(philo, "is thinking", 0);
	}
	return (0);
}

void	routine_check(t_philo *philo)
{
	int	count;

	while (1)
	{
		count = 1;
		sem_wait(philo->data->last_meal_s);
		if (get_time() - philo->last_meal >= philo->data->t_die)
		{
			philo->data->flag = 1;
			print_action(philo, "died", 1);
			sem_post(philo->data->last_meal_s);
			exit (1);
		}
		sem_post(philo->data->last_meal_s);
		if (philo->data->max_meal)
		{
			if (philo->meal < philo->data->max_meal)
				count = 0;
			else if (count)
			{
				philo->data->flag = 1;
				exit (0);
			}
		}
		usleep(1000);
	}
}
