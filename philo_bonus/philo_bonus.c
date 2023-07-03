/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 12:43:22 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/07/03 13:23:16 by tlemos-m         ###   ########.fr       */
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
	return (0);
}
