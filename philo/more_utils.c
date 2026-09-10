/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efittant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:33:32 by efittant          #+#    #+#             */
/*   Updated: 2025/05/14 14:33:35 by efittant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	str_dig(char *c)
{
	int	i;

	i = 0;
	while (c[i])
	{
		if (c[i] < 48 || c[i] > 57)
			return (-1);
		i++;
	}
	return (0);
}

int	ft_atoi(char *str)
{
	int			i;
	long long	result;

	i = 0;
	result = 0;
	if (str[i] == '+')
		i++;
	if (str_dig(&str[i]) == -1)
		return (-1);
	if (str[i])
	{
		while (str[i] >= 48 && str[i] <= 57)
			result = result * 10 + str[i++] - 48;
	}
	if (result == 0 || result > 2147483647)
		return (-1);
	return ((int)result);
}

long	sleep_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
		return (0);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	better_usleep(long time, t_philo *philo)
{
	long	start_sleep;

	start_sleep = sleep_time();
	while (sleep_time() < (start_sleep + time))
	{
		if (sleep_time() >= (start_sleep + time))
			return ;
		if (return_its_over(philo) == 1)
			return ;
		usleep(500);
	}
}

int	create_failed(int i)
{
	static int	failed = 0;

	if (i == 1)
		failed = 1;
	return (failed);
}
