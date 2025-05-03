#include"philo.h"

void	destroy_everything(t_philo *philo, t_data *data)
{
	if (data)
		free(data);
	if (philo)
		free_list(philo);
}
void	free_list(t_philo *phil)
{
	t_philo *cur;
	t_philo *next;

	cur = phil;
	if (!phil)
		return ;
	while (1)
	{
		next = cur->next;
		free(cur);
		if (next == phil || next == NULL)
			return ;
		cur = next;
	}
}