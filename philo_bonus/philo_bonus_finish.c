/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_finish.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 15:00:40 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/07/03 15:02:13 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	free(data->forks);
	free(data->philo);
}
