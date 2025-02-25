#ifndef PHILO_H
# define PHILO_H

// stuff to include
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

// structs
typedef struct s_data
{
	pthread_t		monitor_id;
	int				its_over;
	pthread_mutex_t	end;
	int 			n_phils; // tot phil number
	long			t_die;
	long			t_eat;
	long			t_sleep;
	int				n_meals;
	pthread_mutex_t	message;
	long			start;
	pthread_mutex_t	time;
}					t_data;

typedef struct s_philo
{
	int 			philo; // number of philosopher
	pthread_t		thread_id;
	int				meals_eaten;
	long			last_meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	right_fork;
	struct s_data	*data;
	struct s_philo	*next;
}				t_philo;

// prototypes
// philo
t_philo	*create_philos(char **args);
void				initialise_data(char **args, t_data **data);

//routine
void				*life_cycle(void *arg);
void				eat(t_philo *phil);

// libft
int					ft_atoi(const char *str);
size_t				ft_strlen(const char *str);
void	*die_alone(void *arg);
int		lonely_philo(char **args);

// free &error
//void				errors(char *msg, t_philo **data);
void	destroy_everything(t_philo *phil);
void	destroy_list(t_philo *phil);


// utils
long				return_time(int start, t_philo *philo);
int					is_ready(t_philo *phil);
void				*full_or_dead(void *arg);
int	return_its_over(t_philo *philo);
int					monitor_ready(t_philo *phil);
void	unlock(t_philo *phil);
void	lock(t_philo *phil);
void	start_time(t_philo *philo);
#endif
