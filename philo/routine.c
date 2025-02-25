#include "philo.h"

void	eat(t_philo *phil)	//avoid deadlocks
{
	lock(phil);
	if(return_its_over(phil) != 1)
	{
		if(pthread_mutex_lock(&phil->data->message)!= 0)
			return (printf("Error locking mutex\n"), destroy_everything(phil));
		printf("%ld %d has taken a fork\n", return_time(0,phil), phil->philo);
		printf("%ld %d is eating\n", return_time(0, phil), phil->philo);		
		if(pthread_mutex_unlock(&phil->data->message)!= 0)
			return (printf("Error locking mutex\n"), destroy_everything(phil));
		phil->last_meal = return_time(0, phil);
		usleep(phil->data->t_eat * 1000);
		phil->meals_eaten++;
	}
	unlock(phil);
}

void *life_cycle(void *arg)	//ok
{
	t_philo	*phil;

	phil = (t_philo *) arg;
	while (is_ready(phil) == 0)
		;
	//start_time(phil);
	
	phil->last_meal = return_time(0, phil);
	if(phil->philo % 2 == 0)
		usleep(phil->data->t_eat / 2);
	while (phil->meals_eaten != phil->data->n_meals)
	{
		if(return_its_over(phil) != 1)
			eat(phil);
		if(return_its_over(phil) == 1)
			return (NULL);
		if(return_its_over(phil) != 1)
		{
			if(pthread_mutex_lock(&phil->data->message)!= 0)
				return (printf("Error locking mutex\n"), destroy_everything(phil), NULL);
			printf("%ld %d is sleeping\n", return_time(0, phil), phil->philo);
			if(pthread_mutex_unlock(&phil->data->message)!= 0)
				return (printf("Error locking mutex\n"), destroy_everything(phil), NULL);
			usleep(phil->data->t_sleep * 1000);
		}
		if(return_its_over(phil) != 1)
		{
			if(pthread_mutex_lock(&phil->data->message)!= 0)
				return (printf("Error locking mutex\n"), destroy_everything(phil), NULL);
			printf("%ld %d is thinking\n", return_time(0, phil), phil->philo);
			if(pthread_mutex_unlock(&phil->data->message)!= 0)
				return (printf("Error locking mutex\n"), destroy_everything(phil), NULL);
		}
			
	}
	return (NULL);
}

void	*die_alone(void *arg)
{
	t_philo	*phil;

	phil = (t_philo *) arg;
	if(pthread_mutex_lock(&phil->right_fork)!= 0)
		return (printf("Error locking mutex\n"), destroy_everything(phil), NULL);
	usleep(phil->data->t_die);
	printf("%ld %d died\n", phil->data->t_die, 1);
	if(pthread_mutex_unlock(&phil->right_fork) != 0)
		return (printf("Error unlocking mutex\n"), destroy_everything(phil), NULL);
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
