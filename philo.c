#include "philo.h"

void	initialise(char **args, t_data **data)
{
	*data = (t_data *) malloc(sizeof(t_data));
	if (!data)
		return (write(2, "Allocation failed\n", 18), exit(1));
	(*data)->n_phils = ft_atoi(args[1]);
	(*data)->t_die = ft_atoi(args[2]);
	(*data)->t_eat = ft_atoi(args[3]);
	(*data)->t_sleep = ft_atoi(args[4]);
	if (args[5])
		(*data)->n_food = ft_atoi(args[5]);
	else
		(*data)->n_food = 0;

}

int main(int argc, char **argv)
{
	t_data	*data;

	if (argc < 5 || argc > 6)
		return (write(2, "Invalid number of arguments\n", 28), exit(1), 1);
	initialise(argv, &data);

}
