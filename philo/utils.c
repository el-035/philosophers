#include "philo.h"

long	return_time(int flag)
{
	struct timeval	time;
	static long		start;

	if (flag == 1)
	{
		gettimeofday(&time, NULL);
		start = time.tv_sec * 1000 + time.tv_usec / 1000;
	}
	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000 - start);
}

int	monitor_ready(t_data *phil)
{
	t_data	*cur;
	int		monitor;
	int		i;

	cur = phil;
	monitor = 1;
	i = 0;
	while (i < phil->n_phils)
	{
		//printf("%lu\n", cur->monitor_id);
		if (cur->monitor_id == 0)
			monitor = 0;
		cur = cur->next;
		i++;
	}
	return (monitor);
}

int	is_ready(t_data *phil)
{
	t_data	*start;
	int		ready;
	int		count;
	int		monitor;

	count = phil->n_phils;
	ready = 1;
	start = phil;
	while (start->next != NULL)
	{
		if (start->thread_id == 0)
			ready = 0;
		start = start->next;
		count--;
		if (start == phil)
			break ;
	}
	monitor = monitor_ready(phil);
	if (count != 0)
		ready = 0;
	if (monitor == 0)
		ready = 0;
	return (ready);
}

void	init_monitoring(t_data *phil)
{
	t_data	*cur;
	int		i;

	i = 0;
	cur = phil->next;
	if (pthread_create(&phil->monitor_id, NULL, full_or_dead, phil) != 0)
		printf("Error thread\n"); // error handling
	while (cur != phil)
	{
		cur->monitor_id = phil->monitor_id;
		cur = cur->next;
	}
}

void	*full_or_dead(void *arg)
{
	t_data	*phil;
	t_data	*cur;
	int		i;
	int		full_belly;
	int		death;

	phil = (t_data *) arg;
	usleep(50);
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
