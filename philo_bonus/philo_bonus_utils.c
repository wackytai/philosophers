/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:04:27 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/07/05 11:26:16 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_input(int argc, char **argv, t_data *data)
{
	int	i;
	int	res;

	i = 0;
	while (++i < argc)
	{
		res = ft_atoi(argv[i]);
		if (res <= 0)
			return (-1);
		if (i == 1)
			data->n = res;
		else if (i == 2)
			data->t_die = res * 1000;
		else if (i == 3)
			data->t_eat = res * 1000;
		else if (i == 4)
			data->t_sleep = res * 1000;
		else if (i == 5)
			data->max_meal = res;
	}
	if (argc == 5)
		data->max_meal = 0;
	return (0);
}

int	ft_atoi(char *str)
{
	int			i;
	long long	res;

	i = 0;
	res = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+')
		i++;
	if (str[i] == '-')
		return (-1);
	while (str[i] > 47 && str[i] < 58)
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0')
		return (-1);
	if (res < INT_MIN || res > INT_MAX)
		return (-1);
	return (res);
}

time_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, 0);
	return (time.tv_sec * 1000 + (time.tv_usec / 1000));
}

time_t	sync_time(t_data *data)
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

	if (!end)
		return ;
	time = get_time() - philo->data->t_start;
	sem_wait(philo->data->write_s);
	printf("%lu %i %s\n", time, philo->n_philo, str);
	sem_post(philo->data->write_s);
}
