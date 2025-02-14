#include "philo.h"
void *life_cycle(void *arg)
{
	t_data	*phil;
	int i = 0;

	phil = (t_data *) arg;
	while (phil->n_meals && i++ < phil->n_meals)
		printf("philosopher %d is taking a shit\n", phil->philo);
/* 	printf("philosopher %d exists, or does it?\n", phil->philo);
	printf("philosopher %d is thinking\n", phil->philo); */
	return (NULL);
}

t_data	*create_philosophers(char **args)
{
	t_data	*first;
	t_data	*prev;
	t_data	*new;
	int		i;

	i = 0;
	first = NULL;
	while (i < ft_atoi(args[1], &first))
	{
		new = (t_data *) malloc(sizeof(t_data));
		if (!new)
			errors("Allocation failed\n", &first);	//here everything need to be freed
		memset(new, 0, sizeof(t_data));
		initialise_data(args, i, &new);
		if (pthread_create(&new->thread_id, NULL, life_cycle, new) != 0)
			printf("Error thread\n");	//error handling
		printf("created philo %d\n", new->philo);
		if (!first)
			first = new;
		else
			prev->next = new;
		prev = new;
		i++;
	}
	if (prev)
		prev->next = first;
	return (first);
}
void	initialise_data(char **args, int i, t_data **phil)
{
	(*phil)->philo = i + 1;
	(*phil)->n_phils = ft_atoi(args[1], phil);
	(*phil)->t_die = ft_atoi(args[2], phil);
	(*phil)->t_eat = ft_atoi(args[3], phil);
	(*phil)->t_sleep = ft_atoi(args[4], phil);
	if (args[5])
		(*phil)->n_meals = ft_atoi(args[5], phil);
	else
		(*phil)->n_meals = -1;
}


int main(int argc, char **argv)
{
	t_data	*philo;
	t_data	*temp;
	int		tot;

	if (argc < 5 || argc > 6)
		errors("Invalid number of arguments\n", &philo);
	tot = ft_atoi(argv[1], NULL);
	philo = create_philosophers(argv);
	temp = philo;
	while (tot-- > 0)
	{
		pthread_join(temp->thread_id, NULL);
		temp = temp->next;
	}

}
