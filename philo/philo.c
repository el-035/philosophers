/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efittant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:33:42 by efittant          #+#    #+#             */
/*   Updated: 2025/05/14 14:33:44 by efittant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_helper(t_philo **prev, t_philo **first, t_philo **cur)
{
	if (!*first)
		*first = *cur;
	else
	{
		(*prev)->next = *cur;
		(*cur)->left_fork = &(*prev)->right_fork;
	}
	*prev = *cur;
}

t_philo	*create_philos(char **args, int tot, t_data *data)
{
	t_philo	*first;
	t_philo	*cur;
	t_philo	*prev;
	int		i;

	prev = NULL;
	i = 0;
	first = NULL;
	while (i < tot)
	{
		cur = (t_philo *)malloc(sizeof(t_philo));
		if (!cur)
			return (NULL);
		if (init_philo(args, i++, &cur) != 0)
			return (free(cur), free_list(first), first = NULL, NULL);
		cur->data = data;
		create_helper(&prev, &first, &cur);
	}
	if (prev)
	{
		prev->next = first;
		first->left_fork = &prev->right_fork;
	}
	return (first);
}

int	join_threads(t_philo *philo, int i)
{
	t_philo	*cur;

	cur = philo;
	if (pthread_join(philo->data->monitor_id, NULL) != 0)
		return (-1);
	while (i-- >= 0)
	{
		if (pthread_join(cur->thread_id, NULL) != 0)
			return (-1);
		if (cur->next == philo)
			break ;
		cur = cur->next;
	}
	return (0);
}

int	start_threads(t_philo *philo, t_data *data)
{
	t_philo	*cur;
	int		i;

	cur = philo;
	pthread_mutex_lock(&philo->data->init);
	if (pthread_create(&data->monitor_id, NULL, full_or_dead, philo) != 0)
		return (pthread_mutex_unlock(&philo->data->init), -1);
	pthread_mutex_unlock(&philo->data->init);
	i = 0;
	while (cur)
	{
		pthread_mutex_lock(&cur->data->init);
		if (pthread_create(&cur->thread_id, NULL, life_cycle, cur) != 0)
		{
			return_create_failed(1);
			pthread_mutex_unlock(&cur->data->init);
			break ;
		}
		pthread_mutex_unlock(&cur->data->init);
		if (cur->next == philo)
			break ;
		cur = cur->next;
		i++;
	}
	return (join_threads(philo, i));
}

int	main(int argc, char **argv)
{
	t_philo	*philo;
	t_data	*data;

	if (argc < 5 || argc > 6)
		return (printf("Error\nInvalid input\n"), -1);
	if (check_input(argv) == -1)
		return (printf("Error\nInvalid input\n"), -1);
	if (ft_atoi(argv[1]) == 1)
		return (lonely_philo(argv), 1);
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (-1);
	if (init_data(data) == -1)
		return (free(data), -1);
	philo = create_philos(argv, ft_atoi(argv[1]), data);
	if (!philo)
		return (destroy_everything(philo, data), -1);
	if (start_threads(philo, data) == -1)
		return (destroy_everything(philo, data), -1);
	destroy_everything(philo, data);
}
