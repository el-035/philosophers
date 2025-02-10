#ifndef PHILO_H
# define PHILO_H

//stuff to include
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<stdio.h>
#include<pthread.h>


//structs
typedef struct	s_data
{
	int n_phils;
	int t_die;
	int t_eat;
	int t_sleep; 
	int n_food;
}				t_data;

//prototypes
//philo

//libft
int	ft_atoi(const char *str, t_data **data);
size_t	ft_strlen(const char *str);

//free &error
void	errors(char *msg, t_data **data);
#endif