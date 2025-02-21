#include "philo.h"

t_data	*create_philosophers(char **args)
{
	t_data	*first;
	t_data	*prev;
	t_data	*cur;
	int		i;

	i = 0;
	first = NULL;
	while (i < ft_atoi(args[1]))
	{
		cur = (t_data *) malloc(sizeof(t_data));
		if (!cur)
			return (destroy_everything(cur), NULL);
		initialise_data(args, i++, &cur);
		if (pthread_create(&cur->thread_id, NULL, life_cycle, cur) != 0)
			return (destroy_everything(cur), NULL);
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

void	initialise_data(char **args, int i, t_data **phil)
{
	memset(*phil, 0, sizeof(t_data));
	(*phil)->philo = i + 1;
	(*phil)->n_phils = ft_atoi(args[1]);
	(*phil)->t_die = ft_atoi(args[2]);
	(*phil)->t_eat = ft_atoi(args[3]);
	(*phil)->t_sleep = ft_atoi(args[4]);
	if (args[5])
		(*phil)->n_meals = ft_atoi(args[5]);
	else
		(*phil)->n_meals = -1;
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

//check life cycle and full or dead for errors

int main(int argc, char **argv)	//remove all exits
{
	t_data	*philo;
	t_data	*temp;
	int		tot;

	if (argc < 5 || argc > 6)	//seg fault
		return(printf("Error\nInvalid input\n"), -1);
	if(check_input(argv) == -1)
		return(printf("Error\nInvalid input\n"), -1);
	tot = ft_atoi(argv[1]);
	philo = create_philosophers(argv);
	if (!philo)
		return(printf("Error\n"), -1);
	temp = philo;
	if (init_monitoring(philo) == -1)
		return (printf("Error thread\n"), -1);
	if (pthread_join(philo->monitor_id, NULL) != 0)
		return (printf("Error\n"), destroy_everything(philo), -1);
	while (tot-- > 0)	//check that they worked
	{
		if (pthread_join(temp->thread_id, NULL) != 0)
		return (printf("Error\n"), destroy_everything(philo), -1);
		if (pthread_mutex_init(&temp->right_fork, NULL) != 0)
		return (printf("Error\n"), destroy_everything(philo), -1);
		temp = temp->next;
	}
	destroy_everything(philo);
	return (0);
}
