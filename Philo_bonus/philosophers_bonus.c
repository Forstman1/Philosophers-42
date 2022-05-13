/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 14:31:06 by sahafid           #+#    #+#             */
/*   Updated: 2022/05/13 14:31:08 by sahafid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo_bonus.h"


void	*philosophers(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2)
		usleep(100);
	while (!(philo->rules->dead))
	{
		philo_eats(philo);
		philo_sleeping(philo);
		philo_thinking(philo);
	}
	return (0);
}


int	lunching_threads(t_philo *philo, t_rules rules)
{
	int		i;
	t_philo	*lst;
	int		id;

	i = 1;
	id = 0;
	lst = philo;
	if (!lst)
		return (1);
	while (lst && i <= lst->rules->nb_philo)
	{
		if (id == 0)
		{
			pthread_create(&(lst->thread_id), NULL, &philosophers, lst);
			lst->last_time_eated = time_stamp();
			lst = lst->next;
		}
		else
			id = fork();
		i++;
	}
	return (0);
}


int	all_functions(t_philo **philo, t_rules *rules, char **argv)
{
	if (checking_arguments(argv))
		return (1);
	if (entring_arguments(rules, argv))
		return (1);
	if (initing_philosophers(philo, rules))
		return (1);
	if (lunching_threads(*philo, *rules))
		return (1);
	return (0);
}


int	main(int argc, char	*argv[])
{
	t_rules	rules;
	t_philo	*philo;
	int		j;
	int		i;

	i = 0;
	if (argc != 5 && argc != 6)
		return (write(2, "entre the correct amount of arguments\n", 39));
	if (all_functions(&philo, &rules, argv))
		return (write(2, "ERROR ON THE ARGUMENTS\n", 24));
	return (0);
}