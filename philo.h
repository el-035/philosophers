#ifndef PHILO_H
# define PHILO_H

//stuff to include
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<stdio.h>
//#include


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
int	ft_atoi(const char *str);

#endif