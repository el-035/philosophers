#include "philo.h"

void	eat(t_data *phil)	//avoid deadlocks
{
	lock(phil);
	if(*(phil->its_over) != 1)
	{
		if(pthread_mutex_lock(&phil->message)!= 0)
			return (printf("Error locking mutex\n"), destroy_everything(phil));
		printf("%ld %d has taken a fork\n", return_time(0), phil->philo);
		printf("%ld %d is eating\n", return_time(0), phil->philo);		
		if(pthread_mutex_unlock(&phil->message)!= 0)
			return (printf("Error locking mutex\n"), destroy_everything(phil));
		phil->last_meal = return_time(0);
		usleep(phil->t_eat * 1000);
		phil->meals_eaten++;
	}
	unlock(phil);
}

void *life_cycle(void *arg)	//ok
{
	t_data	*phil;

	phil = (t_data *) arg;
	while (is_ready(phil) == 0)
		;
	phil->last_meal = return_time(0);
	if(phil->philo % 2 == 0)
		usleep(phil->t_eat / 2);
	while (phil->meals_eaten != phil->n_meals)
	{
		if(*(phil->its_over) != 1)
			eat(phil);
		if(*(phil->its_over) == 1)
			return (NULL);
		if(*(phil->its_over) != 1)
		{
			if(pthread_mutex_lock(&phil->message)!= 0)
				return (printf("Error locking mutex\n"), destroy_everything(phil), NULL);
			printf("%ld %d is sleeping\n", return_time(0), phil->philo);
			if(pthread_mutex_unlock(&phil->message)!= 0)
				return (printf("Error locking mutex\n"), destroy_everything(phil), NULL);
			usleep(phil->t_sleep * 1000);
		}
		if(*(phil->its_over) != 1)
		{
			if(pthread_mutex_lock(&phil->message)!= 0)
				return (printf("Error locking mutex\n"), destroy_everything(phil), NULL);
			printf("%ld %d is thinking\n", return_time(0), phil->philo);
			if(pthread_mutex_unlock(&phil->message)!= 0)
				return (printf("Error locking mutex\n"), destroy_everything(phil), NULL);
		}
			
	}
	return (NULL);
}

void	*die_alone(void *arg)
{
	t_data	*phil;

	phil = (t_data *) arg;
	if(pthread_mutex_lock(&phil->right_fork)!= 0)
		return (printf("Error locking mutex\n"), destroy_everything(phil), NULL);
	usleep(phil->t_die);
	printf("%ld %d died\n", phil->t_die, phil->philo);
	if(pthread_mutex_unlock(&phil->right_fork) != 0)
		return (printf("Error unlocking mutex\n"), destroy_everything(phil), NULL);
	return (NULL);
}

int	lonely_philo(char **args)
{
	t_data	*philo;
	
	philo = (t_data *) malloc(sizeof(t_data));
		if (!philo)
			return (destroy_everything(philo), -1);
	initialise_data(args,0, &philo);
	if (pthread_create(&philo->thread_id, NULL, die_alone, philo) != 0)
			return (destroy_everything(philo), -1);
	if (pthread_join(philo->thread_id, NULL) != 0)
			return (printf("Error joining thread\n"), destroy_everything(philo), -1);
	if (pthread_mutex_init(&philo->right_fork, NULL) != 0)
			return (printf("Error initialising mutex\n"), destroy_everything(philo), -1);
	destroy_list(philo);
	return (0);
}
