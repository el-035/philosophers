#ifndef PHILO_H
# define PHILO_H

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
	int			philo;
	pthread_t	thread_id;
	int			n_phils;
	long		t_die;
	long		t_eat;
	long		t_sleep;
	int			n_meals;
	int			meals_eaten;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	right_fork;
	long			last_meal;
	struct s_data	*data;
	struct s_philo	*next;
}				t_philo;

typedef struct s_data
{
	pthread_t	monitor_id;
	pthread_mutex_t	init;
	pthread_mutex_t	time;
	long			start;
	int			over;

}				t_data;


//routine
void	*life_cycle(void *arg);

// monitoring
void	*full_or_dead(void *arg);

//solo
int	lonely_philo(char **args);

//utils
int	is_ready(t_philo *first);
void	start_time(t_data *data);
long	return_time(t_philo *philo);
void	lock(t_philo *phil);
int	return_its_over(t_philo *philo);
void	init_time(t_philo *philo);
void	print(t_philo *phil, int action, long time);
//int	return_its_full(t_philo *philo);
//long	sleep_time();

//libft
int	ft_atoi(const char *str);

//free
void	free_list(t_philo *phil);
void	destroy_everything(t_philo *philo, t_data *data);

#endif