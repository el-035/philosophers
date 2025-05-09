#include"philo.h"

void	*full_or_dead(void *arg)
{
	t_philo	*phil;
	t_philo *cur;
	long	cur_time;
	int		full;

	phil = (t_philo *) arg;
	while (is_ready(phil) == 1)
		;
	while (1)
	{
		cur = phil;
		full = 1;
		while (1)
		{
			pthread_mutex_lock(&cur->data->time);
			cur_time = return_time(cur);
		
			if ((cur_time - cur->last_meal) > cur->t_die)	//or >=?
			{
				pthread_mutex_lock(&cur->data->init);
				(cur->data->over) = 1;
				pthread_mutex_unlock(&cur->data->init);
				/* usleep(3000);	//probably unnecessary */
				printf("%ld %d died\n", cur_time, cur->philo);
				return (pthread_mutex_unlock(&cur->data->time), NULL);
			}
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
