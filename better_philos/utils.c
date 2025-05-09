#include"philo.h"

void	init_time(t_philo *philo)
{
	t_philo *cur;

	pthread_mutex_lock(&philo->data->time);
	start_time(philo->data);
	pthread_mutex_unlock(&philo->data->time);
	cur = philo;
	while (cur)
	{
		pthread_mutex_lock(&philo->data->time);
		cur->last_meal = /* return_time(philo); */ philo->data->start;
		pthread_mutex_unlock(&philo->data->time);
		if (cur->next == philo)
			break ;
		cur = cur->next;
	}
}

int	is_ready(t_philo *first)
{
	t_philo *cur;

	cur = first;
	pthread_mutex_lock(&first->data->init);
	if (!first->data->monitor_id)
		return (pthread_mutex_unlock(&first->data->init), 1);
	pthread_mutex_unlock(&first->data->init);
	while(1)
	{
		pthread_mutex_lock(&cur->data->init);
		if (!cur->thread_id)
			return (pthread_mutex_unlock(&cur->data->init), 1);
		pthread_mutex_unlock(&cur->data->init);
		cur = cur->next;
		if (cur == first)
			break;
	}
	init_time(first);
	return 0;
}

void	start_time(t_data *data)
{
	struct timeval	time;
	long	start;

	if (gettimeofday(&time, NULL) != 0)
		return ;
	start = time.tv_sec * 1000 + time.tv_usec / 1000;
	data->start = start;

}

long	return_time(t_philo *philo)
{
	struct timeval	time;

	long	res;
	if (gettimeofday(&time, NULL) != 0)
		return (0);
	res = time.tv_sec * 1000 + time.tv_usec / 1000 - philo->data->start;
	return (res);
}
long	sleep_time()
{
	struct timeval	time;

	long	res;
	if (gettimeofday(&time, NULL) != 0)
		return (0);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
int	return_its_over(t_philo *philo)
{
	int	end;

	pthread_mutex_lock(&philo->data->init);
	end = philo->data->over;
	pthread_mutex_unlock(&philo->data->init);
	return (end);
}
