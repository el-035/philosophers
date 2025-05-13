#include"philo.h"

int		death_check(t_philo *phil)
{
	long	meal;
	t_philo	*cur;

	cur = phil;
	while (return_its_over(phil) == 0)
	{
		pthread_mutex_lock(&cur->data->time);
		meal = cur->last_meal;
		pthread_mutex_unlock(&cur->data->time);
		if ((return_time(cur) - meal) >= cur->t_die)
		{
			pthread_mutex_lock(&cur->data->init);
			(cur->data->over) = 1;
			pthread_mutex_unlock(&cur->data->init);
			print(cur, DIE, return_time(cur));
			return (1);
		}
		cur = cur->next;
		if (cur == phil)
			break ;
	}
	return (0);
}

int	belly_check(t_philo *phil)
{
	int	full;
	t_philo *cur;


	cur = phil;
	full = 1;
	while (return_its_over(phil) == 0)
	{
		pthread_mutex_lock(&cur->data->time);
		if (cur->meals_eaten < cur->n_meals)
			full = 0;
		pthread_mutex_unlock(&cur->data->time);			
		cur = cur->next;
		if (cur == phil)
			break ;
	}
	return (full);
	
}

void	*full_or_dead(void *arg)
{
	t_philo	*phil;

	phil = (t_philo *) arg;
	while (is_ready(phil) == 1)
		;
	while (return_its_over(phil) == 0)
	{
		if (death_check(phil) == 1)
			return (NULL);
		if (phil->n_meals != -1)
		{
			if (belly_check(phil) == 1)
			{
				pthread_mutex_lock(&phil->data->init);
				(phil->data->over) = 1;
				pthread_mutex_unlock(&phil->data->init);
				return (NULL);
			}
		}
	}
	return (NULL);
}
