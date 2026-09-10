/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efittant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:33:50 by efittant          #+#    #+#             */
/*   Updated: 2025/05/14 14:33:51 by efittant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock(t_philo *phil)
{
	long	cur_time;

	if (phil->philo % 2 == 0)
	{
		pthread_mutex_lock(phil->left_fork);
		print(phil, FORK, return_time(phil));
		pthread_mutex_lock(&phil->right_fork);
		print(phil, FORK, return_time(phil));
	}
	else if (phil->philo % 2 != 0)
	{
		pthread_mutex_lock(&phil->right_fork);
		print(phil, FORK, return_time(phil));
		pthread_mutex_lock(phil->left_fork);
		print(phil, FORK, return_time(phil));
	}
	cur_time = return_time(phil);
	pthread_mutex_lock(&phil->data->time);
	phil->last_meal = cur_time;
	pthread_mutex_unlock(&phil->data->time);
	print(phil, EAT, return_time(phil));
}

void	eat(t_philo *phil)
{
	if (return_its_over(phil) != 1)
		lock(phil);
	better_usleep(phil->t_eat, phil);
	pthread_mutex_unlock(phil->left_fork);
	pthread_mutex_unlock(&phil->right_fork);
	pthread_mutex_lock(&phil->data->time);
	phil->meals_eaten++;
	pthread_mutex_unlock(&phil->data->time);
}

void	nap(t_philo *phil)
{
	if (return_its_over(phil) == 1)
		return ;
	print(phil, SLEEP, return_time(phil));
	better_usleep(phil->t_sleep, phil);
}

void	think(t_philo *phil)
{
	if (return_its_over(phil) == 1)
		return ;
	print(phil, THINK, return_time(phil));
	if ((phil->n_phils % 2 != 0) && return_its_over(phil) != 1)
	{
		if (phil->t_eat >= phil->t_sleep)
			better_usleep((phil->t_eat - phil->t_sleep + 1), phil);
	}
}

void	*life_cycle(void *arg)
{
	t_philo	*phil;

	phil = (t_philo *)arg;
	while (is_ready(phil) == 1)
		;
	pthread_mutex_lock(&phil->data->init);
	if (create_failed(0) == 1)
		return (pthread_mutex_unlock(&phil->data->init), NULL);
	pthread_mutex_unlock(&phil->data->init);
	if (phil->philo % 2 == 0)
		usleep(phil->t_eat * 1000 / 2);
	while (return_its_over(phil) != 1)
	{
		eat(phil);
		nap(phil);
		think(phil);
	}
	return (NULL);
}
