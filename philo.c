/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 13:43:00 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/06/22 14:51:31 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo	philos;

	if (argc < 5 || argc > 6 || check_input(argv, argc, &philos) < 0)
	{
		printf("%s usage: philo_n t_die t_eat t_sleep n_meals\n", argv[0]);
		exit(1);
	}
	return (0);
}
