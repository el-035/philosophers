#include "philo.h"

long	return_time(int flag)
{
	struct timeval	time;
	_Atomic static long		start;
	_Atomic long	res;

	if (flag == 1)
	{
		if (gettimeofday(&time, NULL) != 0)
			return (0);
		start = time.tv_sec * 1000 + time.tv_usec / 1000;
	}
	if (gettimeofday(&time, NULL) != 0)
		return (0);
	res = time.tv_sec * 1000 + time.tv_usec / 1000 - start;
	return (res);
}

int	monitor_ready(t_philo *phil)
{
	t_philo	*cur;
	int		i;

	cur = phil;
	i = 0;
	while (i < phil->data->n_phils)
	{
		if (cur->data->monitor_id == 0)
			return (0);
		cur = cur->next;
		i++;
	}
	return (1);
}

int	is_ready(t_philo *phil)
{
	t_philo	*cur;
	int		count;

	count = phil->data->n_phils;
	cur = phil;
	while (count > 0)
	{
		if (cur->thread_id == 0)
			return (0);
		if (!cur->next && phil->data->n_phils != 1)
			return (0);
		cur = cur->next;
		count--;
	}
	if (monitor_ready(phil) == 0)
		return (0);
	return_time(1);
	return (1);
}

void	lock(t_philo *phil)
{
	if (phil->left_fork < &phil->right_fork)
	{
		if(pthread_mutex_lock(phil->left_fork)!= 0)
			return (printf("Error locking mutex\n"), destroy_everything(phil));
		if(pthread_mutex_lock(&phil->right_fork) != 0)
			return (printf("Error locking mutex\n"), destroy_everything(phil));
	}
	else
	{
		if(pthread_mutex_lock(&phil->right_fork) != 0)
			return (printf("Error locking mutex\n"), destroy_everything(phil));
		if(pthread_mutex_lock(phil->left_fork)!= 0)
			return (printf("Error locking mutex\n"), destroy_everything(phil));
	}
}

void	unlock(t_philo *phil)
{
	if (phil->left_fork < &phil->right_fork)
	{
		if(pthread_mutex_unlock(phil->left_fork) != 0)
			return (printf("Error unlocking mutex\n"), destroy_everything(phil));
		if(pthread_mutex_unlock(&phil->right_fork) != 0)
			return (printf("Error unlocking mutex\n"), destroy_everything(phil));
	}
	else
	{
		if(pthread_mutex_unlock(&phil->right_fork) != 0)
			return (printf("Error unlocking mutex\n"), destroy_everything(phil));
		if(pthread_mutex_unlock(phil->left_fork) != 0)
			return (printf("Error unlocking mutex\n"), destroy_everything(phil));
	}
}