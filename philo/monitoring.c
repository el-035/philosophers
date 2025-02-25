#include "philo.h"

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
				if(pthread_mutex_lock(&phil->message)!= 0)
					return (printf("Error locking mutex\n"), destroy_everything(phil), NULL);
				printf("%ld %d died\n", return_time(0), cur->philo);
				/* if(pthread_mutex_unlock(&phil->message)!= 0)
					return (printf("Error locking mutex\n"), destroy_everything(phil), NULL); */
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