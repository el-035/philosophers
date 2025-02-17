#include"philo.h"

long	return_time()
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return(time.tv_usec / 1000);
}