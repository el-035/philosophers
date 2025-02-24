#include "philo.h"

void	eat(t_data *phil)	//avoid deadlocks
{
	lock(phil);
	if(*(phil->its_over) != 1)
	{
		printf("%ld %d has taken a fork\n", return_time(0), phil->philo);
		printf("%ld %d is eating\n", return_time(0), phil->philo);
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
			printf("%ld %d is sleeping\n", return_time(0), phil->philo);
			usleep(phil->t_sleep * 1000);
		}
		if(*(phil->its_over) != 1)
			printf("%ld %d is thinking\n", return_time(0), phil->philo);
	}
	return (NULL);
}

int	init_monitoring(t_data *phil)	//ok
{
	t_data	*cur;

	if (pthread_create(&phil->monitor_id, NULL, full_or_dead, phil) != 0)
		return (-1);
/* 	if (!phil->next)
		return (0); */
	cur = phil->next;
	while (cur != phil)
	{
		cur->monitor_id = phil->monitor_id;
		cur = cur->next;
	}
	return (0);
}

void	*full_or_dead(void *arg)
{
	t_data	*phil;
	t_data	*cur;
	int		i;
	int		full_belly;

	phil = (t_data *) arg;
	while (is_ready(phil) == 0)
		;
	while (1)
	{
		i = 0;
		cur = phil;
		full_belly = 0;
		while (i < phil->n_phils)
		{
			if (return_time(0) - cur->last_meal > cur->t_die)
			{
				*(cur->its_over) = 1;
				usleep(5);	//mmh find a better way
				printf("%ld %d died\n", return_time(0), cur->philo);
				return (NULL);
			}
			if (cur->meals_eaten == cur->n_meals)
				full_belly++;
			cur = cur->next;
			i++;
		}
		if (full_belly == phil->n_phils)
			return (*(cur->its_over) = 1, NULL);
	}
}
