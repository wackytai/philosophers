/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 14:13:32 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/07/06 12:12:16 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_input(char **argv, int argc, t_attr *data)
{
	int	i;
	int	res;

	i = 0;
	while (++i < argc)
	{
		res = ft_atoi(argv[i]);
		if (res <= 0)
			return (-1);
		else if (i == 1)
			data->n = res;
		else if (i == 2)
			data->t_die = (time_t)res;
		else if (i == 3)
			data->t_eat = (time_t)res * 1000;
		else if (i == 4)
			data->t_sleep = (time_t)res * 1000;
		else if (i == 5)
			data->max_meal = res;
	}
	if (argc == 5)
		data->max_meal = 0;
	return (0);
}

int	ft_atoi(char *str)
{
	long long	res;
	int			i;

	res = 0;
	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		return (-1);
	if (str[i] == '+')
		i++;
	while (str[i] >= 48 && str[i] <= 57)
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0')
		return (-1);
	if (res > INT_MAX || res < INT_MIN)
		return (-1);
	return (res);
}

time_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, 0);
	return (time.tv_sec * 1000 + (time.tv_usec / 1000));
}

void	sync_time(t_attr *data)
{
	time_t	time;

	time = data->t_start - get_time();
	if (time > 0)
		usleep(time * 1000);
	return ;
}

void	print_action(t_philo *philo, char *str, int end)
{
	time_t	time;

	if (!end && check_flag(philo->attr))
		return ;
	time = get_time() - philo->attr->t_start;
	pthread_mutex_lock(&philo->attr->write_m);
	printf("%lu %i %s\n", time, philo->n_philo, str);
	pthread_mutex_unlock(&philo->attr->write_m);
}
