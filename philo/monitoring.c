#include "philo.h"

int	return_its_over(t_philo *philo)
{
	int	end;

	if(pthread_mutex_lock(&philo->data->end)!= 0)
		return (printf("Error locking mutex\n"), destroy_everything(NULL), 0);
	end = philo->data->its_over;
	if(pthread_mutex_unlock(&philo->data->end)!= 0)
		return (printf("Error unlocking mutex\n"), destroy_everything(NULL), 0);
	return (end);
}

void	*full_or_dead(void *arg)
{
	t_philo	*phil;
	t_philo	*cur;
	int		i;
	int 	full_belly;

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
			if (return_time(cur) - cur->last_meal > cur->data->t_die)
			{
				pthread_mutex_lock(&phil->data->end);
				(cur->data->its_over) = 1;
				pthread_mutex_unlock(&phil->data->end);
					

				pthread_mutex_lock(&phil->data->message);
				printf("%ld %d died\n", return_time(cur), cur->philo);
				pthread_mutex_unlock(&phil->data->message);		//somewhere else but where
					
				
				return (NULL);
			}
			
			if (cur->meals_eaten == cur->n_meals)
				full_belly++;
						cur = cur->next;
			i++;
		}
		if (full_belly == phil->data->n_phils)
		{
			pthread_mutex_lock(&phil->data->end);
				
			(cur->data->its_over) = 1;
			pthread_mutex_unlock(&phil->data->end);
				
			return (NULL);
		}
	}
}