#include"philo.h"

int	is_ready(t_philo *first)
{
	t_philo *cur;
	int		tot;

	cur = first;
	tot = first->n_phils;
	pthread_mutex_lock(&first->data->init);
	if (!first->data->monitor_id)
		return (pthread_mutex_unlock(&first->data->init), 1);
	pthread_mutex_unlock(&first->data->init);
	while(tot-- > 0)
	{
		pthread_mutex_lock(&cur->data->init);
		if (!cur->thread_id)
			return (pthread_mutex_unlock(&cur->data->init), 1);
		pthread_mutex_unlock(&cur->data->init);
		cur = cur->next;
	}
	return 0;
}