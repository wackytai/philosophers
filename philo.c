/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 13:43:00 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/06/29 15:02:19 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_attr	data;

	if (argc < 5 || argc > 6 || check_input(argv, argc, &data) < 0)
	{
		printf("%s usage: philo_n t_die t_eat t_sleep n_meals\n", argv[0]);
		exit(1);
	}
	data.philos = (t_philo *)malloc(sizeof(t_philo) * data.n);
	if (!data.philos)
		exit(printf("Error allocating philos\n"));
	data.forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data.n);
	if (!data.forks)
	{
		free(data.philos);
		exit(printf("Error allocating forks\n"));
	}
	if (fill_philo(&data))
		free_all(data.philos, data.forks, &data);
	if (create_threads(&data))
		free_all(data.philos, data.forks, &data);
	free_all(data.philos, data.forks, &data);
	return (0);
}

int	fill_philo(t_attr *data)
{
	int	i;

	i = -1;
	if (pthread_mutex_init(&data->write_m, 0))
		return (1);
	if (pthread_mutex_init(&data->flag_m, 0))
		return (1);
	data->flag = 0;
	while (++i < data->n)
	{
		if (pthread_mutex_init(&data->forks[i], 0))
			return (1);
		if (pthread_mutex_init(data->philos[i].last_meal_m, 0))
			return (1);
		if (pthread_mutex_init(data->philos[i].n_meal_m, 0))
			return (1);
		data->philos[i].meal = 0;
		data->philos[i].attr = data;
		data->philos[i].n_philo = i + 1;
	}
	assign_forks(data);
	return (0);
}

int	free_all(t_philo *philos, pthread_mutex_t *forks, t_attr *data)
{
	destroy_mutexes(data);
	free(philos);
	free(forks);
	return (0);
}

void	destroy_mutexes(t_attr *data)
{
	int	i;

	i = -1;
	while (++i < data->n)
	{
		if (&data->forks[i])
			pthread_mutex_destroy(&data->forks[i]);
		if (data->philos[i].n_meal_m)
			pthread_mutex_destroy(data->philos[i].n_meal_m);
		if (data->philos[i].last_meal_m)
			pthread_mutex_destroy(data->philos[i].last_meal_m);
	}
	if (&data->flag_m)
		pthread_mutex_destroy(&data->flag_m);
	if (&data->write_m)
		pthread_mutex_destroy(&data->write_m);
}

int	create_threads(t_attr *data)
{
	int	i;

	i = -1;
	data->t_start = get_time() + (data->n * 2);
	while (++i < data->n)
	{
		data->philos[i].last_meal = data->t_start;
		if (pthread_create(&data->philos[i].tid, 0, routine, &data->philos[i]))
			return (1);
	}
	if (data->n > 1)
		routine_check(data);
	i = -1;
	while (++i < data->n)
		pthread_join(data->philos[i].tid, 0);
	return (0);
}

void	routine_check(t_attr *data)
{
	(void)data;
	printf("routine check\n");
}
