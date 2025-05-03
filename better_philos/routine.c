#include"philo.h"

void	*life_cycle(void *arg)
{
	t_philo	*phil;

	phil = (t_philo *) arg;
	while (is_ready(phil) == 1)
		usleep(100);	//remove
	printf("inside thread of philo %d\n", phil->philo);
	
	return (NULL);
}

