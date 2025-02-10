#include "philo.h"

int	ft_atoi(const char *str, t_data **data)	//needs to free data if error
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			return (error("Negative input\n", data), 0);
		i++;
	}
	if (str[i])
	{
		while (str[i] >= 48 && str[i] <= 57)
			result = result * 10 + str[i++] - 48;
	}
	return (result);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}