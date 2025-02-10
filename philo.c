#include "philo.h"

void	initialise(char **args, t_data **data)
{
	*data = (t_data *) malloc(sizeof(t_data));
	if (!*data)
		errors("Allocation failed\n", data);
	(*data)->n_phils = ft_atoi(args[1], data);
	(*data)->t_die = ft_atoi(args[2], data);
	(*data)->t_eat = ft_atoi(args[3], data);
	(*data)->t_sleep = ft_atoi(args[4], data);
	if (args[5])
		(*data)->n_food = ft_atoi(args[5], data);
	else
		(*data)->n_food = -1;

}

int main(int argc, char **argv)
{
	t_data	*data;

	data = NULL;

	if (argc < 5 || argc > 6)
		errors("Invalid number of arguments\n", &data);
	initialise(argv, &data);

}
