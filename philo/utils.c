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
	t_data	*cur;
	int		count;

	count = phil->n_phils;
	cur = phil;
	while (count > 0)
	{
		if (cur->thread_id == 0)
			return (0);
		if (!cur->next && phil->n_phils != 1)
			return (0);
		cur = cur->next;
		count--;
	}
	if (monitor_ready(phil) == 0)
		return (0);
	return_time(1);
	return (1);
}

