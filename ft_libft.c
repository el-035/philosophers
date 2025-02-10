#include "philo.h"

int	ft_atoi(const char *str)	//needs to free data if error
{
	int	i;
	int	result;
	int	n;

	n = 1;
	i = 0;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			return (write(2, "Error\n", 6), exit(1), 0);
		i++;
	}
	if (str[i])
	{
		while (str[i] >= 48 && str[i] <= 57)
			result = result * 10 + str[i++] - 48;
	}
	return (result * n);
}