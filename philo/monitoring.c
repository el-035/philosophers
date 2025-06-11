/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efittant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:33:23 by efittant          #+#    #+#             */
/*   Updated: 2025/05/14 14:33:24 by efittant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	death_check(t_philo *phil)
{
	long	meal;
	t_philo	*cur;

	cur = phil;
	while (return_its_over(phil) == 0)
	{
		pthread_mutex_lock(&cur->data->time);
		meal = cur->last_meal;
		pthread_mutex_unlock(&cur->data->time);
		if ((return_time(cur) - meal) >= cur->t_die)
		{
			pthread_mutex_lock(&cur->data->init);
			(cur->data->over) = 1;
			pthread_mutex_unlock(&cur->data->init);
			print(cur, DIE, return_time(cur));
			return (1);
		}
		cur = cur->next;
		if (cur == phil)
			break ;
	}
	return (0);
}

int	belly_check(t_philo *phil)
{
	int		full;
	t_philo	*cur;

	cur = phil;
	full = 1;
	while (return_its_over(phil) == 0)
	{
		pthread_mutex_lock(&cur->data->time);
		if (cur->meals_eaten < cur->n_meals)
			full = 0;
		pthread_mutex_unlock(&cur->data->time);
		cur = cur->next;
		if (cur == phil)
			break ;
	}
	return (full);
}

void	*full_or_dead(void *arg)
{
	t_philo	*phil;

	phil = (t_philo *)arg;
	while (is_ready(phil) == 1)
		;
	pthread_mutex_lock(&phil->data->init);
	if (phil->data->philos != phil->data->threads)
		return (pthread_mutex_unlock(&phil->data->init), NULL);
	pthread_mutex_unlock(&phil->data->init);
	while (return_its_over(phil) == 0)
	{
		if (death_check(phil) == 1)
			return (NULL);
		if (phil->n_meals != -1)
		{
			if (belly_check(phil) == 1)
			{
				pthread_mutex_lock(&phil->data->init);
				(phil->data->over) = 1;
				pthread_mutex_unlock(&phil->data->init);
				return (NULL);
			}
		}
	}
	return (NULL);
}

void	print(t_philo *phil, int action, long time)
{
	char	*message;

	if (action == 1)
		message = "has taken a fork";
	else if (action == 2)
		message = "is eating";
	else if (action == 3)
		message = "is sleeping";
	else if (action == 4)
		message = "is thinking";
	else if (action == 5)
		message = "died";
	if (return_its_over(phil) == 1 && action != DIE)
		return ;
	pthread_mutex_lock(&phil->data->init);
	printf("%ld %d %s\n", time, phil->philo, message);
	pthread_mutex_unlock(&phil->data->init);
}
