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

int	return_create_failed(int i)
{
	static int	failed = 0;

	if (i == 1)
		failed = 1;
	return (failed);
}
