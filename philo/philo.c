#include "philo.h"

t_philo	*create_philos(char **args)	//not ok
{
	t_data *data;
	t_philo	*first;
	t_philo	*prev;
	t_philo	*cur;
	int		i;

	i = 0;
	first = NULL;
	data = (t_data *) malloc(sizeof(t_data));
	if (!data)
			return (destroy_everything(first), NULL);
	initialise_data(args, &data);
	while (++i <= ft_atoi(args[1]))
	{
		cur = (t_philo *) malloc(sizeof(t_philo));
		if (!cur)
			return (destroy_everything(cur), NULL);
		memset(cur, 0, sizeof(t_philo));
		cur->data = data;
		cur->philo = i;
		if (pthread_create(&cur->thread_id, NULL, life_cycle, cur) != 0)
			return (destroy_everything(cur), NULL);
		if (pthread_mutex_init(&cur->right_fork, NULL) != 0)
			return (printf("Error initialising mutex\n"), destroy_everything(first), NULL);
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

void	initialise_data(char **args, t_data **data)	//ok
{
	memset(*data, 0, sizeof(t_data));

	(*data)->its_over = 0;
	(*data)->n_phils = ft_atoi(args[1]);
	(*data)->t_die = ft_atoi(args[2]);
	(*data)->t_eat = ft_atoi(args[3]);
	(*data)->t_sleep = ft_atoi(args[4]);
	if (args[5])
		(*data)->n_meals = ft_atoi(args[5]);
	else
		(*data)->n_meals = -1;
	if (pthread_mutex_init(&(*data)->message, NULL) != 0)
			return (printf("Error initialising mutex\n"), destroy_everything(NULL));
	if (pthread_mutex_init(&(*data)->threads, NULL) != 0)
		return (printf("Error initialising mutex\n"), destroy_everything(NULL));
}

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
int	join_threads(t_philo *phil)
{
	int		tot;
	t_philo	*temp;

	temp = phil;
	tot = phil->data->n_phils;
	if (pthread_join(phil->data->monitor_id, NULL) != 0)
		return (printf("Error joining thread\n"), destroy_everything(phil), -1);
	while (tot-- > 0)
	{
		if (pthread_join(temp->thread_id, NULL) != 0)
			return (printf("Error joining thread\n"), destroy_everything(phil), -1);
		temp = temp->next;
	}
	return (0);
}
int main(int argc, char **argv)	//check life cycle and full or dead for errors
{
	t_philo	*philo;
	
	if (argc < 5 || argc > 6)
		return(printf("Error\nInvalid input\n"), -1);
	if(check_input(argv) == -1)
		return(printf("Error\nInvalid input\n"), -1);
	if (ft_atoi(argv[1]) == 1)
		return(lonely_philo(argv));
	philo = create_philos(argv);
	if (!philo)
		return(printf("Error creating philosophers\n"), -1);
	
	if (pthread_create(&philo->data->monitor_id, NULL, full_or_dead, philo) != 0)	
		return (printf("Error thread\n"), destroy_everything(philo), -1);
	join_threads(philo);
	return (0);
}
