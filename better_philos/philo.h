#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

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

	struct s_data	*data;
	struct s_philo	*next;
}				t_philo;

typedef struct s_data
{
	pthread_t	monitor_id;
	pthread_mutex_t	time;
	pthread_mutex_t	food;
	pthread_mutex_t	init;
	int			over;

}				t_data;


//routine
void	*life_cycle(void *arg);

// monitoring
void	*full_or_dead(void *arg);

//utils
int	is_ready(t_philo *first);

//libft
int	ft_atoi(const char *str);

//free
void	free_list(t_philo *phil);

#endif