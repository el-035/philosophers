#include"philo.h"

void	*die_alone(void *arg)
{
	t_philo	*phil;

	phil = (t_philo *) arg;
	pthread_mutex_lock(&phil->right_fork);
	usleep(phil->data->t_die);
	printf("%ld %d died\n", phil->data->t_die, 1);
	pthread_mutex_unlock(&phil->right_fork);

	return (NULL);
}

int	lonely_philo(char **args)
{
	t_philo	*philo;
	t_data	*data;
	
	philo = (t_philo *) malloc(sizeof(t_philo));
		if (!philo)
			return ( -1);
	data = (t_data *) malloc(sizeof(t_data));
		if (!data)
			return (-1);
	memset(data, 0, sizeof(t_data));
	data->t_die = ft_atoi(args[2]);
	philo->data = data;
	if (pthread_mutex_init(&philo->right_fork, NULL) != 0)
			return (printf("Error initialising mutex\n"),  -1);
	if (pthread_create(&philo->thread_id, NULL, die_alone, philo) != 0)
			return ( -1);
	if (pthread_join(philo->thread_id, NULL) != 0)
			return (printf("Error joining thread\n"),  -1);
	//destroy_list(philo);
	free(data);
	return (0);
}
