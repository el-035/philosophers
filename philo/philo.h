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
	int 			philo; // number of philosopher
	pthread_t		thread_id;
	pthread_t		monitor_id;
	int 			n_phils; // tot phil number
	long			t_die;
	long			t_eat;
	long			t_sleep;
	int				n_meals;
	int				meals_eaten;
	int				last_meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	right_fork;
	struct s_data	*next;
}					t_data;

// prototypes
// philo
t_data				*create_philosophers(char **args);
void				initialise_data(char **args, int i, t_data **phil);

//routine
void				*life_cycle(void *arg);
void				eat(t_data *phil);

// libft
int					ft_atoi(const char *str);
size_t				ft_strlen(const char *str);

// free &error
//void				errors(char *msg, t_data **data);
void	destroy_everything(t_data *phil);
void	destroy_list(t_data *phil);
void	destroy_monitor(t_data *phil);
void	destroy_threads(t_data *phil);

// utils
long				return_time(int start);
int					is_ready(t_data *phil);
void				*full_or_dead(void *arg);
int				init_monitoring(t_data *phil);
int					monitor_ready(t_data *phil);

#endif