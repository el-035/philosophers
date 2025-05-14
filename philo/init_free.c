/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efittant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:12:00 by efittant          #+#    #+#             */
/*   Updated: 2025/05/14 14:12:04 by efittant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_input(char **args)
{
	if (ft_atoi(args[1]) == -1)
		return (-1);
	if (ft_atoi(args[2]) == -1)
		return (-1);
	if (ft_atoi(args[3]) == -1)
		return (-1);
	if (ft_atoi(args[4]) == -1)
		return (-1);
	if (args[5])
	{
		if (ft_atoi(args[5]) == -1)
			return (-1);
	}
	return (0);
}

int	init_philo(char **args, int i, t_philo **phil)
{
	memset(*phil, 0, sizeof(t_philo));
	(*phil)->philo = i + 1;
	(*phil)->n_phils = ft_atoi(args[1]);
	(*phil)->t_die = ft_atoi(args[2]);
	(*phil)->t_eat = ft_atoi(args[3]);
	(*phil)->t_sleep = ft_atoi(args[4]);
	if (args[5])
		(*phil)->n_meals = ft_atoi(args[5]);
	else
		(*phil)->n_meals = -1;
	if (pthread_mutex_init(&(*phil)->right_fork, NULL) != 0)
		return (-1);
	return (0);
}

t_data	*init_data(t_data *data)
{
	data->over = 0;
	if (pthread_mutex_init(&data->time, NULL) != 0)
		return (NULL);
	if (pthread_mutex_init(&data->init, NULL) != 0)
		return (NULL);
	return (data);
}

void	destroy_everything(t_philo *philo, t_data *data)
{
	if (data)
	{
		pthread_mutex_destroy(&data->init);
		pthread_mutex_destroy(&data->time);
		free(data);
	}
	if (philo)
		free_list(philo);
}

void	free_list(t_philo *phil)
{
	t_philo	*cur;
	t_philo	*next;

	cur = phil;
	if (!phil)
		return ;
	while (1)
	{
		next = cur->next;
		pthread_mutex_destroy(&cur->right_fork);
		free(cur);
		if (next == phil || next == NULL)
			return ;
		cur = next;
	}
}
