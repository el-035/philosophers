#include "philo.h"

void	eat(t_philo *phil)	//avoid deadlocks
{
	long	cur_time;
	
	
	lock(phil);
	if(return_its_over(phil) != 1)
	{
		pthread_mutex_lock(&phil->time);
		cur_time = return_time(phil);
		phil->last_meal = cur_time;
		pthread_mutex_unlock(&phil->time);
		
		pthread_mutex_lock(&phil->data->message);
		printf("%ld %d has taken a fork\n", cur_time, phil->philo);
		printf("%ld %d is eating\n", cur_time, phil->philo);		
		pthread_mutex_unlock(&phil->data->message);
		usleep(phil->data->t_eat * 1000);
		
	
	}
	pthread_mutex_unlock(phil->left_fork);
	pthread_mutex_unlock(&phil->right_fork);
	
	pthread_mutex_lock(&phil->time);
	phil->meals_eaten++;
	pthread_mutex_unlock(&phil->time);
}

void *life_cycle(void *arg)	//ok
{
	t_philo	*phil;
	long	cur_time;

	phil = (t_philo *) arg;
	while (is_ready(phil) == 0)
		;
	pthread_mutex_lock(&phil->time);
	start_time(phil);
	phil->last_meal = return_time(phil);
	pthread_mutex_unlock(&phil->time);
	
	if(phil->philo % 2 == 0)
		usleep(phil->data->t_eat / 2);
	while (1)
	{
		if(return_its_over(phil) != 1)
			eat(phil);
		if(return_its_over(phil) == 1)
			return (NULL);
		if(return_its_over(phil) != 1)
		{
			pthread_mutex_lock(&phil->time);
			cur_time = return_time(phil);
			pthread_mutex_unlock(&phil->time);
			
			pthread_mutex_lock(&phil->data->message);
			printf("%ld %d is sleeping\n", cur_time, phil->philo);
			pthread_mutex_unlock(&phil->data->message);
			usleep(phil->data->t_sleep * 1000);
		}
		if(return_its_over(phil) != 1)
		{
			pthread_mutex_lock(&phil->time);
			cur_time = return_time(phil);
			pthread_mutex_unlock(&phil->time);

			pthread_mutex_lock(&phil->data->message);
			printf("%ld %d is thinking\n", cur_time, phil->philo);
			pthread_mutex_unlock(&phil->data->message);
		}
			
	}
	return (NULL);
}

void	*die_alone(void *arg)
{
	t_philo	*phil;

	phil = (t_philo *) arg;
	pthread_mutex_lock(&phil->right_fork);
	usleep(phil->data->t_die);
	printf("%ld %d died\n", phil->data->t_die, 1);
	pthread_mutex_unlock(&phil->right_fork);

	return (NULL);
}

int	lonely_philo(char **args)
{
	t_philo	*philo;
	t_data	*data;
	
	philo = (t_philo *) malloc(sizeof(t_philo));
		if (!philo)
			return (destroy_everything(philo), -1);
	data = (t_data *) malloc(sizeof(t_data));
		if (!data)
			return (destroy_everything(NULL), -1);
	memset(data, 0, sizeof(t_data));
	data->t_die = ft_atoi(args[2]);
	philo->data = data;
	if (pthread_mutex_init(&philo->right_fork, NULL) != 0)
			return (printf("Error initialising mutex\n"), destroy_everything(philo), -1);
	if (pthread_create(&philo->thread_id, NULL, die_alone, philo) != 0)
			return (destroy_everything(philo), -1);
	if (pthread_join(philo->thread_id, NULL) != 0)
			return (printf("Error joining thread\n"), destroy_everything(philo), -1);
	destroy_list(philo);
	free(data);
	return (0);
}
