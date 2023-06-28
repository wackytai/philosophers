/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 13:31:18 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/06/28 11:22:24 by tlemos-m         ###   ########.fr       */
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

# define HUNGRY 0
# define THINKING 1
# define SLEEPING 2

struct	s_attr;
typedef struct s_philo
{
	time_t			last_meal;
	pthread_mutex_t	*last_meal_m;
	pthread_mutex_t	*n_meal_m;
	pthread_mutex_t	*fork_1;
	pthread_mutex_t	*fork_2;
	pthread_t		tid;
	int				meal;
	struct s_attr	*attr;
	int				n_philo;
}	t_philo;

typedef struct s_attr
{
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*write_m;
	time_t			t_start;
	time_t			t_die;
	time_t			t_eat;
	time_t			t_sleep;
	int				max_meal;
	int				flag;
	int				n;
	pthread_mutex_t	*flag_m;
}	t_attr;

/* philo.c */
int		main(int argc, char **argv);
int		fill_philo(t_attr *data);
int		free_all(t_philo *philos, pthread_mutex_t *forks, t_attr *data);
void	destroy_mutexes(t_attr *data);
int		create_threads(t_attr *data);
void	*routine(void *data);
void	routine_check(t_attr *data);

/* philo_utils.c */
int		check_input(char **argv, int argc, t_attr *data);
int		ft_atoi(char *str);
time_t	get_time(void);
void	print_action(t_attr *data, int flag);

/* actions.c */
void	assign_forks(t_attr *data);
void	eat(t_attr *data);
void	think(t_attr *data);
void	sleep(t_attr *data);

/* actions_utils.c */
int		check_death(t_attr *data);

#endif