#include "philo.h"

void	destroy_everything(t_data *phil)
{
	destroy_monitor(phil);
	destroy_threads(phil);
	destroy_list(phil);
}

void	destroy_monitor(t_data *phil)
{
	if (!phil)
		return ;
	if (phil->monitor_id != 0)
	{
		if (pthread_detach(phil->monitor_id) != 0)
			printf("Error detaching thread\n");
		phil->monitor_id = 0;
	}
}

void	destroy_threads(t_data *phil)
{
	t_data *cur;
	int		i;

	i = 0;
	cur = phil;
	if (!phil)
		return ;
	while (i < phil->n_phils)
	{
		if (cur->thread_id != 0)
		{
			if (pthread_detach(cur->thread_id) != 0)
				printf("Error detaching thread\n");
			cur->thread_id = 0;
		}
		if (pthread_mutex_destroy(&cur->right_fork) != 0)
			printf("Error destroying mutex\n");
		cur = cur->next;
		i++;
	}
}
	
void	destroy_list(t_data *phil)
{
	t_data *cur;
	t_data *prev;

	if (!phil)
		return ;
	cur = phil;
	while (cur)
	{
		prev = cur;
		cur = cur->next;
		free(prev);
	}
}
