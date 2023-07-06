/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 12:43:53 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/07/06 09:12:46 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <fcntl.h>
# include <limits.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <sys/types.h>

struct	s_data;
typedef struct s_philo
{
	int				n_philo;
	int				meal;
	time_t			last_meal;
	pthread_t		tid;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int		n;
	int		flag;
	int		max_meal;
	pid_t	*pid;
	sem_t	*forks;
	sem_t	*write_s;
	sem_t	*last_meal_s;
	time_t	t_start;
	time_t	t_die;
	time_t	t_eat;
	time_t	t_sleep;
	t_philo	*philo;
}	t_data;

/* philo_bonus.c */
int		main(int argc, char **argv);
int		create_philos(t_data *data);
int		handle_philo(t_philo *philo);
void	*routine(void *philos);
void	routine_check(t_philo *philo);

/* philo_bonus_actions.c */
int		one_philosopher(t_philo *philo);
void	eat(t_philo *philo);

/* philo_bonus_utils.c */
int		check_input(int argc, char **argv, t_data *data);
int		ft_atoi(char *str);
time_t	get_time(void);
void	sync_time(t_data *data);
void	print_action(t_philo *philo, char *str, int end);

/* philo_bonus_finish.c */
int		init_sem(t_data *data);
void	init_pid(t_data *data);
void	close_semaphores(t_data *data);
void	free_all(t_data *data);
void	finish_processes(t_data *data);

#endif