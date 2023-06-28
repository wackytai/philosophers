/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 11:21:20 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/06/28 11:24:58 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_attr *data)
{
	int	i;

	i = -1;
	while (++i < data->n)
	{
		if ((get_time() - data->philos[i].last_meal) > data->t_die)
			return (1);
	}
	return (0);
}
