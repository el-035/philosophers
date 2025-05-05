#include"philo.h"

int	check_input(char **args)
{
	if(ft_atoi(args[1]) == -1)
		return (-1);
	if(ft_atoi(args[2]) == -1)
		return (-1);
	if(ft_atoi(args[3]) == -1)
		return (-1);
	if(ft_atoi(args[4]) == -1)
		return (-1);
	if (args[5])
	{
		if(ft_atoi(args[5]) == -1)
			return (-1);
	}
	return (0);
}

void	init_philo(char **args, int i, t_philo **phil)
{
	memset(*phil, 0, sizeof(t_philo));
	(*phil)->philo = i + 1;
	(*phil)->n_phils = ft_atoi(args[1]);
	(*phil)->t_die = ft_atoi(args[2]);
	(*phil)->t_eat = ft_atoi(args[3]);
	(*phil)->t_sleep = ft_atoi(args[4]);
	if (args[5])
		(*phil)->n_meals = ft_atoi(args[5]);
	else
		(*phil)->n_meals = -1;
	pthread_mutex_init(&(*phil)->right_fork, NULL);
	//pthread_mutex_init(&(*phil)->food, NULL);

}

t_data	*init_data(/* t_philo *phil,  */t_data *data)
{
	data->over = 0;
	//pthread_mutex_init(&data->time, NULL);
	pthread_mutex_init(&data->time, NULL);
	pthread_mutex_init(&data->init, NULL);
	return (data);
}

t_philo	*create_philos(char **args, int tot, t_data *data)
{
	t_philo	*first;
	t_philo	*cur;
	t_philo	*prev;
	int		i;

	i = 0;
	first = NULL;
	while (i < tot)
	{
		cur = (t_philo *) malloc(sizeof(t_philo));
		if (!cur)
			return (free_list(first), free(data), NULL); //Error handling
		init_philo(args, i++, &cur);
		cur->data = data;
		if (!first)
			first = cur;
		else
		{
			prev->next = cur;
			cur->left_fork = &prev->right_fork;
		}
		prev = cur;
	}
	if (prev)
	{
		prev->next = first;
		first->left_fork = &prev->right_fork;
	}

	return (first);
}

void	start_threads(t_philo *philo, t_data *data)	//change to int??
{
	t_philo	*cur;

	cur = philo;

	

	pthread_mutex_lock(&philo->data->init);
	pthread_create(&data->monitor_id, NULL, full_or_dead, philo);
	pthread_mutex_unlock(&philo->data->init);
	while (cur)
	{
		/* pthread_mutex_lock(&philo->data->time);
		cur->last_meal = cur->data->start;
		pthread_mutex_unlock(&philo->data->time); */

		pthread_mutex_lock(&cur->data->init);
		pthread_create(&cur->thread_id, NULL, life_cycle, cur);
		pthread_mutex_unlock(&cur->data->init);
		if (cur->next == philo)
			break ;
		cur = cur->next;
	}
	
	cur = philo;
	pthread_join(philo->data->monitor_id, NULL);
	while (cur)
	{
		pthread_join(cur->thread_id, NULL);
		if (cur->next == philo)
		break ;
		cur = cur->next;
	}
}

int main(int argc, char **argv)
{
	t_philo	*philo;
	t_data	*data;

	if (argc < 5 || argc > 6)
		return(printf("Error\nInvalid input\n"), -1);
	if(check_input(argv) == -1)
		return(printf("Error\nInvalid input\n"), -1);
	//ONE PHILO
	if (ft_atoi(argv[1]) == 1)
		return(lonely_philo(argv), 1);
	//MORE PHILOS INITIALISE
	data = (t_data *) malloc (sizeof(t_data));
	if (!data)
		return (-1);
	data = init_data(data);
	philo = create_philos(argv, ft_atoi(argv[1]), data);
	if (!philo)
		return -1;
	//START THREADS
	start_threads(philo, data);

	destroy_everything(philo, data);
}
