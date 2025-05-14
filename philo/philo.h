/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efittant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:38:50 by efittant          #+#    #+#             */
/*   Updated: 2025/05/14 14:38:52 by efittant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define FORK 1
# define EAT 2
# define SLEEP 3
# define THINK 4
# define DIE 5

typedef struct s_philo
{
	int				philo;
	pthread_t		thread_id;
	int				n_phils;
	long			t_die;
	long			t_eat;
	long			t_sleep;
	int				n_meals;
	int				meals_eaten;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	right_fork;
	long			last_meal;
	struct s_data	*data;
	struct s_philo	*next;
}					t_philo;

typedef struct s_data
{
	pthread_t		monitor_id;
	pthread_mutex_t	init;
	pthread_mutex_t	time;
	long			start;
	int				over;

}					t_data;

// main
int					start_threads(t_philo *philo, t_data *data);
int					join_threads(t_philo *philo);
t_philo				*create_philos(char **args, int tot, t_data *data);
void				create_helper(t_philo **prev, t_philo **first,
						t_philo **cur);

// solo
int					lonely_philo(char **args);
void				*die_alone(void *arg);

// routine
void				lock(t_philo *phil);
void				eat(t_philo *phil);
void				nap(t_philo *phil);
void				think(t_philo *phil);
void				*life_cycle(void *arg);

// monitoring
int					death_check(t_philo *phil);
int					belly_check(t_philo *phil);
void				*full_or_dead(void *arg);
void				print(t_philo *phil, int action, long time);

// utils
void				init_time(t_philo *philo);
int					is_ready(t_philo *first);
void				start_time(t_data *data);
long				return_time(t_philo *philo);
int					return_its_over(t_philo *philo);

// more_utils
int					ft_atoi(const char *str);
long				sleep_time(void);
void				better_usleep(long time, t_philo *philo);

// free
int					check_input(char **args);
int					init_philo(char **args, int i, t_philo **phil);
t_data				*init_data(t_data *data);
void				free_list(t_philo *phil);
void				destroy_everything(t_philo *philo, t_data *data);

#endif
