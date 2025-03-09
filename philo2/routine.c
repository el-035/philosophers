#include "philo.h"

void *life_cycle(void *arg)
{
	t_philo	*phil;

	phil = (t_philo *) arg;

	while (is_ready(phil) == 0)
		;

	pthread_mutex_lock(&phil->data->message);
	printf("philo %d entered life cycle\n", phil->philo);
	pthread_mutex_unlock(&phil->data->message);

	return (NULL);
}