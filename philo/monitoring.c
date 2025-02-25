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
	int		full_belly;
	//int		cur_time;

	phil = (t_philo *) arg;
	while (is_ready(phil) == 0)
		;
	start_time(phil);
	
	while (1)
	{
		i = 0;
		cur = phil;
		full_belly = 0;

		while (i < phil->data->n_phils)
		{
			if (return_time(0, phil) - cur->last_meal > cur->data->t_die)
			{
				if(pthread_mutex_lock(&phil->data->end)!= 0)
					return (printf("Error locking mutex\n"), destroy_everything(NULL), NULL);
				(cur->data->its_over) = 1;
				if(pthread_mutex_unlock(&phil->data->end)!= 0)
					return (printf("Error unlocking mutex\n"), destroy_everything(NULL), NULL);

				if(pthread_mutex_lock(&phil->data->message)!= 0)
					return (printf("Error locking mutex\n"), destroy_everything(phil), NULL);
				printf("%ld %d died\n", return_time(0, phil), cur->philo);
				if(pthread_mutex_unlock(&phil->data->message)!= 0)		//somewhere else but where
					return (printf("Error locking mutex\n"), destroy_everything(phil), NULL);
				return (NULL);
			}
			if (cur->meals_eaten == cur->data->n_meals)
				full_belly++;
			cur = cur->next;
			i++;
		}
		if (full_belly == phil->data->n_phils)
		{
			if(pthread_mutex_lock(&phil->data->end)!= 0)
				return (printf("Error locking mutex\n"), destroy_everything(NULL), NULL);
			(cur->data->its_over) = 1;
			if(pthread_mutex_unlock(&phil->data->end)!= 0)
				return (printf("Error unlocking mutex\n"), destroy_everything(NULL), NULL);
			return (NULL);
		}
	}
}