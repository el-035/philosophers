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

int	init_philo(char **args, int i, t_philo **phil)
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
	if (pthread_mutex_init(&(*phil)->right_fork, NULL) != 0)
		return (-1);
	return (0);
}

t_data	*init_data(t_data *data)
{
	data->over = 0;
	if (pthread_mutex_init(&data->time, NULL) != 0)
		return (NULL);
	if (pthread_mutex_init(&data->init, NULL) != 0)
		return (NULL);
	return (data);
}

static void create_helper(t_philo **prev, t_philo **first, t_philo **cur)
{
	if (!*first)
		*first = *cur;
	else
	{
		(*prev)->next = *cur;
		(*cur)->left_fork = &(*prev)->right_fork;
	}
	*prev = *cur;
}

t_philo	*create_philos(char **args, int tot, t_data *data)
{
	t_philo	*first;
	t_philo	*cur;
	t_philo	*prev;

	prev = NULL;
	int		i;
	i = 0;
	first = NULL;
	while (i < tot)
	{
		cur = (t_philo *) malloc(sizeof(t_philo));
		if (!cur)
			return (NULL);
		if (init_philo(args, i++, &cur) != 0)
			return (NULL);
		cur->data = data;
		create_helper(&prev, &first, &cur);
	//	prev = cur;
	}
	if (prev)
	{
		prev->next = first;
		first->left_fork = &prev->right_fork;
	}
	return (first);
}

/* t_philo	*create_philos(char **args, int tot, t_data *data)
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
			return (NULL);
		if (init_philo(args, i++, &cur) != 0)
			return (NULL);
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
} */

int	join_threads(t_philo *philo)
{
	t_philo	*cur;

	cur = philo;
	if (pthread_join(philo->data->monitor_id, NULL) != 0)
		return (-1);
	while (cur)
	{
		if (pthread_join(cur->thread_id, NULL) != 0)
			return (-1);
		if (cur->next == philo)
			break ;
		cur = cur->next;
	}
	return (0);
}

int	start_threads(t_philo *philo, t_data *data)
{
	t_philo	*cur;

	cur = philo;
	pthread_mutex_lock(&philo->data->init);
	if (pthread_create(&data->monitor_id, NULL, full_or_dead, philo) != 0)
		return (-1);
	pthread_mutex_unlock(&philo->data->init);
	while (cur)
	{
		pthread_mutex_lock(&cur->data->init);
		if (pthread_create(&cur->thread_id, NULL, life_cycle, cur) != 0)
			return (-1);
		pthread_mutex_unlock(&cur->data->init);
		if (cur->next == philo)
			break ;
		cur = cur->next;
	}
	return (join_threads(philo));
}

int main(int argc, char **argv)
{
	t_philo	*philo;
	t_data	*data;

	if (argc < 5 || argc > 6)
		return(printf("Error\nInvalid input\n"), -1);
	if(check_input(argv) == -1)
		return(printf("Error\nInvalid input\n"), -1);
	if (ft_atoi(argv[1]) == 1)
		return(lonely_philo(argv), 1);
	data = (t_data *) malloc (sizeof(t_data));
	if (!data)
		return (-1);
	data = init_data(data);
	if (!data)
		return(free(data), printf("here\n"), -1);
	philo = create_philos(argv, ft_atoi(argv[1]), data);
	if (!philo)
		return (destroy_everything(philo, data), -1);
	if (start_threads(philo, data) == -1)
		return(destroy_everything(philo, data), -1);
	destroy_everything(philo, data);
}
