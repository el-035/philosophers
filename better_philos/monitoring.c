#include"philo.h"

int		death_check(t_philo *cur)
{
	long	meal;

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
	return (0);
}

/* int	belly_check(t_philo *cur)
{
	int	full;
	
} */

void	*full_or_dead(void *arg)
{
	t_philo	*phil;
	t_philo *cur;
	int		full;

	phil = (t_philo *) arg;
	while (is_ready(phil) == 1)
		;
	while (return_its_over(phil) == 0)
	{
		cur = phil;
		full = 1;
		while (return_its_over(phil) == 0)
		{
			if (death_check(cur) == 1)
				return (NULL);
			pthread_mutex_lock(&cur->data->time);
			if (cur->meals_eaten < cur->n_meals)
				full = 0;
			pthread_mutex_unlock(&cur->data->time);
			cur = cur->next;
			if (cur == phil)
				break ;
		}
		if (full == 1)
		{
			pthread_mutex_lock(&cur->data->init);
			(cur->data->over) = 1;
			pthread_mutex_unlock(&cur->data->init);
			return (NULL);
		}
	}
	return (NULL);
}
