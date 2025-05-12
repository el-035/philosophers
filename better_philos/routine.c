#include"philo.h"

long	sleep_time()
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
		return (0);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	better_usleep(long	time, t_philo *philo)
{
	long	start_sleep;

	start_sleep = sleep_time();
	while (sleep_time() < (start_sleep + time))
	{
		if (sleep_time() >= (start_sleep + time))
			return ;
		if (return_its_over(philo) == 1)
			return ;
		usleep(500);
	}
}

void	lock(t_philo *phil)
{
	long	cur_time;

	//usleep(500);
	if (phil->philo % 2 == 0)
	{
		pthread_mutex_lock(phil->left_fork);
		pthread_mutex_lock(&phil->right_fork);
		print(phil, FORK, return_time(phil));
		print(phil, FORK, return_time(phil));
	}
	else if (phil->philo % 2 != 0)
	{
		pthread_mutex_lock(&phil->right_fork);
		pthread_mutex_lock(phil->left_fork);
		print(phil, FORK, return_time(phil));
		print(phil, FORK, return_time(phil));
	}
	cur_time = return_time(phil);

	pthread_mutex_lock(&phil->data->time);
	phil->last_meal = cur_time;
	pthread_mutex_unlock(&phil->data->time);

	print(phil, EAT, return_time(phil));
}

void	eat(t_philo *phil)
{
	/* long	cur_time; */

	if (return_its_over(phil) != 1)
		lock(phil);

	/* pthread_mutex_lock(&phil->data->time);
	cur_time = return_time(phil);
	phil->last_meal = cur_time;
	pthread_mutex_unlock(&phil->data->time);
	if (return_its_over(phil) != 1)
	{
		pthread_mutex_unlock(phil->left_fork);
		pthread_mutex_unlock(&phil->right_fork);
		return ;
	}
	pthread_mutex_lock(&phil->data->init);
	printf("%ld %d has taken a fork\n", cur_time, phil->philo);
	printf("%ld %d has taken a fork\n", cur_time, phil->philo);
	printf("%ld %d is eating\n", cur_time, phil->philo);		
	pthread_mutex_unlock(&phil->data->init); */

	better_usleep(phil->t_eat, phil);
	
	pthread_mutex_unlock(phil->left_fork);
	pthread_mutex_unlock(&phil->right_fork);

	pthread_mutex_lock(&phil->data->time);
		phil->meals_eaten++;
	pthread_mutex_unlock(&phil->data->time);
}

void	nap(t_philo *phil)
{
	//long	cur_time;

/* 	pthread_mutex_lock(&phil->data->time);
	cur_time = return_time(phil);
	pthread_mutex_unlock(&phil->data->time); */
	if (return_its_over(phil) == 1)
		return ;
	print(phil, SLEEP, return_time(phil));
		/* pthread_mutex_lock(&phil->data->init);
	printf("%ld %d is sleeping\n", cur_time, phil->philo);
	pthread_mutex_unlock(&phil->data->init); */
	better_usleep(phil->t_sleep, phil);

}

void	think(t_philo *phil)
{
	//long cur_time;


/* 	pthread_mutex_lock(&phil->data->time);
	cur_time = return_time(phil);
	pthread_mutex_unlock(&phil->data->time); */
	if (return_its_over(phil) == 1)
		return ;
	/* pthread_mutex_lock(&phil->data->init);
	printf("%ld %d is thinking\n", cur_time, phil->philo);
	pthread_mutex_unlock(&phil->data->init); */
	print(phil, THINK, return_time(phil));

	
	if ((phil->n_phils % 2 != 0) && return_its_over(phil) != 1)
	{
		if (phil->t_eat >= phil->t_sleep)
			better_usleep((phil->t_eat - phil->t_sleep + 1), phil);
	}
}

void	*life_cycle(void *arg)
{
	t_philo	*phil;

	phil = (t_philo *) arg;

	while (is_ready(phil) == 1)
		;
	
	if(phil->philo % 2 == 0)
		usleep(phil->t_eat * 1000 / 2);
	while (return_its_over(phil) != 1)
	{
		eat(phil);
		if (return_its_over(phil) == 0)
			nap(phil);
		if (return_its_over(phil) == 0)
			think(phil);
		if (return_its_over(phil) == 1)
			return (NULL);	
	}
	return (NULL);
}
