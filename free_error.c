#include "philo.h"

void	error(char *msg, t_data **data)
{
	write(2, "Error\n", 6);
	if (*data && data)
	{
		free (*data);
		data = NULL;
	}
	write(2, msg, ft_strlen(msg));
	exit(1);
}