#include "philo.h"

void	eat(t_data *phil)
{
	full_or_dead(phil);
	pthread_mutex_lock(&phil->right_fork);
	pthread_mutex_lock(phil->left_fork);
	phil->last_meal = return_time(0);
	//full_or_dead(phil);
	printf("%ld %d has taken a fork\n", return_time(0), phil->philo);
	printf("%ld %d is eating\n", return_time(0), phil->philo);
	full_or_dead(phil);
	usleep(phil->t_eat * 1000);
	full_or_dead(phil);
	phil->meals_eaten++;
	pthread_mutex_unlock(&phil->right_fork);
	pthread_mutex_unlock(phil->left_fork);
	full_or_dead(phil);
}

void *life_cycle(void *arg)
{
	t_data	*phil;

	phil = (t_data *) arg;
	while (is_ready(phil) == 0)
		;
	phil->last_meal = return_time(1);
	while (1)
	{
		eat(phil);
		printf("%ld %d is sleeping\n", return_time(0), phil->philo);
		full_or_dead(phil);
		usleep(phil->t_sleep * 1000);
		full_or_dead(phil);
		printf("%ld %d is thinking\n", return_time(0), phil->philo);
		full_or_dead(phil);
	}
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
		initialise_data(args, i++, &new);
		if (pthread_create(&new->thread_id, NULL, life_cycle, new) != 0)
			printf("Error thread\n");	//error handling
		if (!first)
			first = new;
		else
		{
			prev->next = new;
			new->left_fork = &prev->right_fork;
		}
		prev = new;
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
	(*phil)->n_phils = ft_atoi(args[1], phil);
	(*phil)->t_die = ft_atoi(args[2], phil);
	(*phil)->t_eat = ft_atoi(args[3], phil);
	(*phil)->t_sleep = ft_atoi(args[4], phil);
	if (args[5])
		(*phil)->n_meals = ft_atoi(args[5], phil);
	else
		(*phil)->n_meals = -1;
}

int main(int argc, char **argv)	//remove all exits
{
	t_data	*philo;
	t_data	*temp;
	int		tot;

	if (argc < 5 || argc > 6)
		errors("Invalid number of arguments\n", &philo);
	tot = ft_atoi(argv[1], NULL);
	philo = create_philosophers(argv);
	temp = philo;
	while (tot-- > 0)	//check that they worked
	{
		if (pthread_join(temp->thread_id, NULL) != 0)
			return 1; 	//handle error
		pthread_mutex_init(&temp->right_fork, NULL);
		temp = temp->next;
	}
/* 	while (1)
	{
		if (full_or_dead(philo) == 1)
			exit(1);
			destroy_everything()
	} */
}
