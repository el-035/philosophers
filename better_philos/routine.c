#include"philo.h"

void	think_more(t_philo *phil)
{
	long cur_time;
	long t_last_meal;

	if(phil->philo % 2 == 0)
		usleep(3000);
	else
	{
		pthread_mutex_lock(&phil->data->time);
		cur_time = return_time(phil);
		t_last_meal = cur_time - phil->last_meal;
		pthread_mutex_unlock(&phil->data->time);
		if (t_last_meal < (phil->t_die / 2))
			usleep(3000);
	}
}

void	eat(t_philo *phil)
{
	long	cur_time;
	

	lock(phil);
	if(return_its_over(phil) != 1)
	{
		pthread_mutex_lock(&phil->data->time);
		cur_time = return_time(phil);
		phil->last_meal = cur_time;
		pthread_mutex_unlock(&phil->data->time);
		
		pthread_mutex_lock(&phil->data->init);
		printf("%ld %d has taken a fork\n", cur_time, phil->philo);
		printf("%ld %d is eating\n", cur_time, phil->philo);		
		pthread_mutex_unlock(&phil->data->init);
		usleep(phil->t_eat * 1000);
	}
	pthread_mutex_unlock(phil->left_fork);
	pthread_mutex_unlock(&phil->right_fork);
	
	pthread_mutex_lock(&phil->data->time);
	phil->meals_eaten++;
	pthread_mutex_unlock(&phil->data->time);
}

void	*life_cycle(void *arg)
{
	t_philo	*phil;
	long	cur_time;

	phil = (t_philo *) arg;
	
/* 	pthread_mutex_lock(&phil->data->time);
	phil->last_meal = phil->data->start;
	pthread_mutex_unlock(&phil->data->time); */
	
	while (is_ready(phil) == 1)
		usleep(1000);	//remove

	if(phil->philo % 2 == 0)
		usleep(phil->t_eat * 1000 / 2);
	while (return_its_over(phil) != 1)
	{
		if(return_its_over(phil) != 1)
			eat(phil);
		if(return_its_over(phil) != 1)
		{
			pthread_mutex_lock(&phil->data->time);
			cur_time = return_time(phil);
			pthread_mutex_unlock(&phil->data->time);
			
			pthread_mutex_lock(&phil->data->init);
			printf("%ld %d is sleeping\n", cur_time, phil->philo);
			pthread_mutex_unlock(&phil->data->init);
			usleep(phil->t_sleep * 1000);
		}
		if(return_its_over(phil) != 1)
		{
			pthread_mutex_lock(&phil->data->time);
			cur_time = return_time(phil);
			pthread_mutex_unlock(&phil->data->time);

			pthread_mutex_lock(&phil->data->init);
			printf("%ld %d is thinking\n", cur_time, phil->philo);
			pthread_mutex_unlock(&phil->data->init);
			think_more(phil);

		}
	}
	
	return (NULL);
}
