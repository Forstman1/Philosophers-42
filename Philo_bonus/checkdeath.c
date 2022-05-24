/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkdeath.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:59:10 by sahafid           #+#    #+#             */
/*   Updated: 2022/05/24 15:59:11 by sahafid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	checksituation(t_philo *philo)
{
	t_philo	*lst;
	int		test;
	int		i;

	lst = philo;
	test = 0;
	i = 0;
	while (i < lst->rules->nb_philo)
	{
		waitpid(-1, &test, 0);
		if (test != 0)
		{
			i = 1;
			printf("%ld %d died\n", time_stamp() - \
			lst->rules->timestamp, lst->id);
			while (i <= lst->rules->nb_philo)
			{
				kill(lst->process_id, SIGKILL);
				lst = lst->next;
				i++;
			}
			exit(0);
		}
		i++;
	}
}

void	free_all(t_philo **philo, t_rules *rules)
{
	t_philo	*tmp;
	t_philo	*lst;
	int		i;

	lst = *philo;
	i = 1;
	while (i <= lst->rules->nb_philo)
	{
		tmp = lst->next;
		free(lst);
		lst = NULL;
		if (tmp)
			lst = tmp;
		i++;
	}
}
