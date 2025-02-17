#ifndef PHILO_H
# define PHILO_H

//stuff to include
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<stdio.h>
#include<pthread.h>
#include<sys/time.h>

//structs
typedef struct	s_data
{
	int	philo;		//number of philosopher
	pthread_t thread_id;
	int n_phils;	//tot phil number
	int t_die;	
	int t_eat;
	int t_sleep;
	int n_meals;
	pthread_t	*left_fork;
	pthread_t right_fork;
	struct s_data		*next;
}				t_data;



//prototypes
//philo
void *life_cycle(void *arg);
t_data	*create_philosophers(char **args);
void	initialise_data(char **args, int i, t_data **phil);

//libft
int	ft_atoi(const char *str, t_data **data);
size_t	ft_strlen(const char *str);

//free &error
void	errors(char *msg, t_data **data);

//utils
long	return_time();
#endif