#include "philo.h"

int	ft_atoi(const char *str)
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
			return (-1);
		i++;
	}
	if (str[i])
	{
		while (str[i] >= 48 && str[i] <= 57)
			result = result * 10 + str[i++] - 48;
	}
	if (result == 0)
		return (-1);
	return (result);
}

/* size_t	ft_strlen(const char *str) //OK
{
	size_t i;

	i = 0;
	while (str[i])
		i++;
	return (i);
} */