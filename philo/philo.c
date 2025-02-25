#include "philo.h"

t_data	*create_philosophers(char **args)	//ok
{
	t_data	*first;
	t_data	*prev;
	t_data	*cur;
	int		i;
	_Atomic int		end = 0;

	i = 0;
	first = NULL;
	while (i < ft_atoi(args[1]))
	{
		/* if(pthread_mutex_lock(&first->threads)!= 0)
			return (printf("Error locking mutex\n"), destroy_everything(cur), NULL); */
		cur = (t_data *) malloc(sizeof(t_data));
		if (!cur)
			return (destroy_everything(cur), NULL);
		initialise_data(args, i++, &cur);
		cur->its_over = &end;
		if (pthread_create(&cur->thread_id, NULL, life_cycle, cur) != 0)
			return (destroy_everything(cur), NULL);
		if (cur->n_phils == 1)
			return (cur);
		if (!first)
			first = cur;
		else
		{
			prev->next = cur;
			cur->left_fork = &prev->right_fork;
		}
		prev = cur;
		/* if(pthread_mutex_unlock(&first->threads)!= 0)
			return (printf("Error unlocking mutex\n"), destroy_everything(cur), NULL); */
	}
	if (prev)
	{
		prev->next = first;
		first->left_fork = &prev->right_fork;
	}
	return (first);
}

void	initialise_data(char **args, int i, t_data **phil)	//ok
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

int	check_input(char **args)	//OK
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
int	init_threads(t_data *phil)
{
	int	tot;
	t_data	*temp;

	temp = phil;
	tot = phil->n_phils;
	if (pthread_join(phil->monitor_id, NULL) != 0)
		return (printf("Error joining thread\n"), destroy_everything(phil), -1);
	if (pthread_mutex_init(&phil->message, NULL) != 0)
			return (printf("Error initialising mutex\n"), destroy_everything(phil), -1);
	if (pthread_mutex_init(&phil->threads, NULL) != 0)
		return (printf("Error initialising mutex\n"), destroy_everything(phil), -1);
	while (tot-- > 0)
	{
		if (pthread_join(temp->thread_id, NULL) != 0)
			return (printf("Error joining thread\n"), destroy_everything(phil), -1);
		/* if (pthread_mutex_init(&temp->right_fork, NULL) != 0)
			return (printf("Error initialising mutex\n"), destroy_everything(phil), -1); */
		temp = temp->next;
	}
	return (0);
}
int main(int argc, char **argv)	//check life cycle and full or dead for errors
{
	t_data	*philo;
	
	if (argc < 5 || argc > 6)
		return(printf("Error\nInvalid input\n"), -1);
	if(check_input(argv) == -1)
		return(printf("Error\nInvalid input\n"), -1);
	if (ft_atoi(argv[1]) == 1)
		return(lonely_philo(argv));
	philo = create_philosophers(argv);
	if (!philo)
		return(printf("Error creating philosophers\n"), -1);
	if (init_monitoring(philo) == -1)
		return (printf("Error thread\n"), destroy_everything(philo), -1);
	init_threads(philo);
	return (0);
}
