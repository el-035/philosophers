#include"philo.h"

void	destroy_everything(t_philo *philo, t_data *data)
{
	if (data)
	{
		pthread_mutex_destroy(&data->init);
		pthread_mutex_destroy(&data->time);
		free(data);
	}
	if (philo)
		free_list(philo);
}
void	free_list(t_philo *phil)
{
	t_philo *cur;
	t_philo *next;

	cur = phil;
	if (!phil)
		return ;
	while (1)
	{
		next = cur->next;
		pthread_mutex_destroy(&cur->right_fork);
		free(cur);
		if (next == phil || next == NULL)
			return ;
		cur = next;
	}
}