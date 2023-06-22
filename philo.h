/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 13:31:18 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/06/22 14:51:39 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int	n_philos;
	int	n_forks;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int	n_meals;
}	t_philo;

/* philo.c */
int	main(int argc, char **argv);

/* philo_utils.c */
int	check_input(char **argv, int argc, t_philo *philos);
int	ft_atoi(char *str);

#endif