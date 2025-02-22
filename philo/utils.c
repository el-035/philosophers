#include "philo.h"

long	return_time(int flag)	//ok
{
	struct timeval	time;
	static long		start;

	if (flag == 1)
	{
		if (gettimeofday(&time, NULL) != 0)
			return (0);
		start = time.tv_sec * 1000 + time.tv_usec / 1000;
	}
	if (gettimeofday(&time, NULL) != 0)
		return (0);
	return (time.tv_sec * 1000 + time.tv_usec / 1000 - start);
}

int	monitor_ready(t_data *phil)	//ok
{
	t_data	*cur;
	int		i;

	cur = phil;
	i = 0;
	while (i < phil->n_phils)
	{
		if (cur->monitor_id == 0)
			return (0);
		cur = cur->next;
		i++;
	}
	return (1);
}

int	is_ready(t_data *phil)	//OK
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
	if (count != 0 || monitor != 0)
		ready = 0;
	return (ready);
}
