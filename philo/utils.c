#include "philo.h"
void	start_time(t_philo *philo)
{
	struct timeval	time;
	long	start;

	if (gettimeofday(&time, NULL) != 0)
		return ;
	start = time.tv_sec * 1000 + time.tv_usec / 1000;
	philo->start = start;	
}

long	return_time(t_philo *philo)
{
	struct timeval	time;

	long	res;
	if (gettimeofday(&time, NULL) != 0)
		return (0);
	res = time.tv_sec * 1000 + time.tv_usec / 1000 - philo->start;
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
	if (phil->data->monitor_id == 0)
		return 0;
	/* if (monitor_ready(phil) == 0)
		return (0); */
	return (1);
}

void	lock(t_philo *phil)
{
	if (phil->left_fork < &phil->right_fork)
	{
		pthread_mutex_lock(phil->left_fork);
		pthread_mutex_lock(&phil->right_fork);
	}
	else
	{
		pthread_mutex_lock(&phil->right_fork);
		pthread_mutex_lock(phil->left_fork);
	}
}

void	unlock(t_philo *phil)
{
		pthread_mutex_unlock(phil->left_fork);
		pthread_mutex_unlock(&phil->right_fork);
}