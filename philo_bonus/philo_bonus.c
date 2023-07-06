/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 12:43:22 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/07/06 12:07:17 by tlemos-m         ###   ########.fr       */
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
	init_philos(&data);
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
	data->t_start = get_time() + (data->n * 2);
	while (++i < data->n)
	{
		data->pid[i] = fork();
		if (data->pid[i] < 0)
			return (printf("Error forking\n"));
		if (!data->pid[i])
			handle_philo(&data->philo[i]);
	}
	finish_processes(data);
	return (0);
}

int	handle_philo(t_philo *philo)
{
	philo->last_meal = philo->data->t_start;
	if (pthread_create(&philo->tid, 0, routine_check, philo))
		exit(1);
	if (pthread_detach(philo->tid))
		exit(1);
	sync_time(philo->data);
	if (philo->n_philo % 2)
		think(philo);
	while (1)
	{
		eat(philo);
		think(philo);
	}
	return (0);
}

void	*routine_check(void *philos)
{
	t_philo	*philo;

	philo = (t_philo *)philos;
	sync_time(philo->data);
	while (1)
	{
		sem_wait(philo->data->last_meal_s);
		if (philo->data->t_die <= (get_time() - philo->last_meal))
		{
			print_action(philo, "died");
			exit(1);
		}
		sem_post(philo->data->last_meal_s);
		usleep(1000);
	}
	return (0);
}

void	init_philos(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n)
	{
		data->philo[i].meal = 0;
		data->philo[i].data = data;
		data->philo[i].n_philo = i + 1;
	}
	return ;
}
