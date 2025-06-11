/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lonely_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efittant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:14:02 by efittant          #+#    #+#             */
/*   Updated: 2025/05/14 14:14:05 by efittant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*die_alone(void *arg)
{
	t_philo	*phil;

	phil = (t_philo *)arg;
	pthread_mutex_lock(&phil->right_fork);
	printf("%d %d has taken a fork\n", 0, 1);
	usleep(phil->t_die);
	printf("%ld %d died\n", phil->t_die, 1);
	pthread_mutex_unlock(&phil->right_fork);
	return (NULL);
}

static void	free_solo(t_philo *phil)
{
	pthread_mutex_destroy(&phil->right_fork);
	free(phil->data);
	free(phil);
}

int	lonely_philo(char **args)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		return (-1);
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (free(philo), -1);
	memset(data, 0, sizeof(t_data));
	philo->t_die = ft_atoi(args[2]);
	philo->data = data;
	if (pthread_mutex_init(&philo->right_fork, NULL) != 0)
		return (free(philo), free(data), -1);
	if (pthread_create(&philo->thread_id, NULL, die_alone, philo) != 0)
		return (free_solo(philo), -1);
	if (pthread_join(philo->thread_id, NULL) != 0)
		return (free_solo(philo), -1);
	pthread_mutex_destroy(&philo->right_fork);
	free(philo);
	free(data);
	return (0);
}
