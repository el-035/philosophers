#include "philo.h"

void	eat(t_data *phil)
{
	pthread_mutex_lock(&phil->right_fork);
	pthread_mutex_lock(phil->left_fork);
	phil->last_meal = return_time(0);
	printf("%ld %d has taken a fork\n", return_time(0), phil->philo);
	printf("%ld %d is eating\n", return_time(0), phil->philo);
	usleep(phil->t_eat * 1000);
	phil->meals_eaten++;
	pthread_mutex_unlock(&phil->right_fork);
	pthread_mutex_unlock(phil->left_fork);
}

void *life_cycle(void *arg)
{
	t_data	*phil;

	phil = (t_data *) arg;
	//usleep(50);
	while (is_ready(phil) == 0)
		;
	phil->last_meal = return_time(1);
	if(phil->philo % 2 == 0)
		usleep(phil->t_eat / 2);
	while (1)
	{
		eat(phil);
		printf("%ld %d is sleeping\n", return_time(0), phil->philo);
		usleep(phil->t_sleep * 1000);
		printf("%ld %d is thinking\n", return_time(0), phil->philo);
	}
	return (NULL);
}

int	init_monitoring(t_data *phil)
{
	t_data	*cur;

	cur = phil->next;
	if (pthread_create(&phil->monitor_id, NULL, full_or_dead, phil) != 0)
		return (-1);
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
	int		death;

	phil = (t_data *) arg;
	//usleep(50);
	while (is_ready(phil) == 0)
		;
	while (1)
	{
		i = 0;
		cur = phil;
		full_belly = 0;
		death = 0;
		while (i < phil->n_phils)
		{
			if (return_time(0) - cur->last_meal > cur->t_die)
			{
				printf("%ld %d died\n", return_time(0), cur->philo);
				death = 1;
				break ;
			}
			if (cur->meals_eaten == cur->n_meals)
				full_belly++;
			cur = cur->next;
			i++;
		}
		if (death == 1 || full_belly == phil->n_phils)
			exit(1);	//fix here
	}
}