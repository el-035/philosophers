#include"philo.h"

void	*full_or_dead(void *arg)
{
	t_philo	*phil;

	phil = (t_philo *) arg;
	while (is_ready(phil) == 1)
		usleep(100);	//remove
	printf("inside thread of monitoring\n");
	(void) phil;
	return (NULL);
}