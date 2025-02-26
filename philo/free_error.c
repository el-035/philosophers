#include "philo.h"

void	destroy_everything(t_philo *phil)
{

	destroy_list(phil);
}

void destroy_mutex(t_philo *phil)
{
	t_philo *cur;
	int		i;

	i = 0;
	cur = phil;
	if (!phil)
		return ;
	while (i < phil->data->n_phils)
	{
		if (pthread_mutex_destroy(&cur->right_fork) != 0)
			printf("Error destroying mutex\n");
		cur = cur->next;
		i++;
	}
	if (pthread_mutex_destroy(&cur->data->end) != 0)
			printf("Error destroying mutex\n");
	if (pthread_mutex_destroy(&cur->data->message) != 0)
			printf("Error destroying mutex\n");
	/* if (pthread_mutex_destroy(&cur->data->eat) != 0)
			printf("Error destroying mutex\n"); */
}

	
void	destroy_list(t_philo *phil)
{
	t_philo *cur;
	t_philo *prev;

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
