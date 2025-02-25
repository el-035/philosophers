#include "philo.h"

void	*full_or_dead(void *arg)
{
	t_philo	*phil;
	t_philo	*cur;
	int		i;
	int		full_belly;

	phil = (t_philo *) arg;
	while (is_ready(phil) == 0)
		;
	while (1)
	{
		i = 0;
		cur = phil;
		full_belly = 0;
		while (i < phil->data->n_phils)
		{
			if (return_time(0) - cur->last_meal > cur->data->t_die)
			{
				(cur->data->its_over) = 1;
				if(pthread_mutex_lock(&phil->data->message)!= 0)
					return (printf("Error locking mutex\n"), destroy_everything(phil), NULL);
				printf("%ld %d died\n", return_time(0), cur->philo);
				/* if(pthread_mutex_unlock(&phil->message)!= 0)
					return (printf("Error locking mutex\n"), destroy_everything(phil), NULL); */
				return (NULL);
			}
			if (cur->meals_eaten == cur->data->n_meals)
				full_belly++;
			cur = cur->next;
			i++;
		}
		if (full_belly == phil->data->n_phils)
			return ((cur->data->its_over) = 1, NULL);
	}
}