#include"philo.h"

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