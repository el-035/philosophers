#include"philo.h"

void	lock(t_philo *phil)
{
	if (phil->philo % 2 == 0)
	{
		pthread_mutex_lock(&phil->right_fork);
		pthread_mutex_lock(phil->left_fork);
	}
	else
	{
		pthread_mutex_lock(phil->left_fork);
		pthread_mutex_lock(&phil->right_fork);
	}
}

void	eat(t_philo *phil)
{
	long	cur_time;

	lock(phil);

	pthread_mutex_lock(&phil->data->time);
	cur_time = return_time(phil);
	phil->last_meal = cur_time;
	pthread_mutex_unlock(&phil->data->time);
	if (return_its_over(phil) == 1)
		return ;
	pthread_mutex_lock(&phil->data->init);
	printf("%ld %d has taken a fork\n", cur_time, phil->philo);
	printf("%ld %d is eating\n", cur_time, phil->philo);		
	pthread_mutex_unlock(&phil->data->init);
	usleep(phil->t_eat * 1000);

	pthread_mutex_unlock(phil->left_fork);
	pthread_mutex_unlock(&phil->right_fork);
	
	pthread_mutex_lock(&phil->data->time);
		phil->meals_eaten++;
	pthread_mutex_unlock(&phil->data->time);
}

void	nap(t_philo *phil)
{
	long	cur_time;

	pthread_mutex_lock(&phil->data->time);
	cur_time = return_time(phil);
	pthread_mutex_unlock(&phil->data->time);
	if (return_its_over(phil) == 1)
		return ;
	pthread_mutex_lock(&phil->data->init);
	printf("%ld %d is sleeping\n", cur_time, phil->philo);
	pthread_mutex_unlock(&phil->data->init);
	usleep(phil->t_sleep * 1000);
}

void	think(t_philo *phil)
{
	long cur_time;
	long t_last_meal;

	pthread_mutex_lock(&phil->data->time);
	cur_time = return_time(phil);
	pthread_mutex_unlock(&phil->data->time);
	if (return_its_over(phil) == 1)
		return ;
	pthread_mutex_lock(&phil->data->init);
	printf("%ld %d is thinking\n", cur_time, phil->philo);
	pthread_mutex_unlock(&phil->data->init);
	
	if ((phil->n_phils % 2 != 0))
	{
		pthread_mutex_lock(&phil->data->time);
		t_last_meal = return_time(phil) - phil->last_meal;
		pthread_mutex_unlock(&phil->data->time);
		if (t_last_meal < (phil->t_sleep + 2000))
			usleep(phil->t_eat / 2 * 1000);
	}
}

void	*life_cycle(void *arg)
{
	t_philo	*phil;

	phil = (t_philo *) arg;
	init_time(phil);

	while (is_ready(phil) == 1)
		;
	if(phil->philo % 2 == 0)
		usleep(phil->t_eat * 1000 / 2);
	while (return_its_over(phil) != 1)
	{
		if(return_its_over(phil) != 1)
			eat(phil);
		if(return_its_over(phil) != 1)
			nap(phil);
		if(return_its_over(phil) != 1)
			think(phil);
	}
	return (NULL);
}
