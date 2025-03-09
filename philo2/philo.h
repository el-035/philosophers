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
	int				n_meals;
	long			t_sleep;
	pthread_mutex_t	message;
	pthread_mutex_t	philo;
}					t_data;

typedef struct s_philo
{
	int 			philo; // number of philosopher
	pthread_t		thread_id;
	int				meals_eaten;
	long			last_meal;
	long			start;
	pthread_mutex_t	eat;
	pthread_mutex_t	time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	right_fork;
	struct s_data	*data;
	struct s_philo	*next;
}				t_philo;

// prototypes
// philo
int	check_input(char **args);


// libft
int					ft_atoi(const char *str);
size_t				ft_strlen(const char *str);

//solo
void	*die_alone(void *arg);
int		lonely_philo(char **args);

//routine
void 	*life_cycle(void *arg);

#endif
