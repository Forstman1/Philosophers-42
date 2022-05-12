/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 11:47:39 by sahafid           #+#    #+#             */
/*   Updated: 2022/04/01 11:47:40 by sahafid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	lunching_threads(t_philo *philo, t_rules rules)
{
	int		i;
	t_philo	*lst;

	i = 1;
	lst = philo;
	if (!lst)
		error();
	while (lst && i <= lst->rules->nb_philo)
	{
		pthread_create(&(lst->thread_id), NULL, &philosophers, lst);
		lst->last_time_eated = time_stamp();
		lst = lst->next;
		i++;
	}
}

void	checkdeath(t_rules *rules, t_philo *philo)
{
	while (1)
	{
		if (rules->nb_philo == rules->philo_eated)
		{
			philo->rules->dead = 1;
			return ;
		}
		if (time_stamp() - philo->last_time_eated > philo->rules->time_to_die)
		{
			printf("%ld philosopher  %d is dead\n", time_stamp() - \
			philo->last_time_eated, philo->id);
			philo->rules->dead = 1;
			return ;
		}
		philo = philo->next;
		usleep(500);
	}
}

int	main(int argc, char	*argv[])
{
	t_rules	rules;
	t_philo	*philo;
	int		j;
	int		i;

	i = 0;
	if (argc != 5 && argc != 6)
		return (write(1, "entre the correct amount of arguments\n", 39));
	checking_arguments(argv);
	entring_arguments(&rules, argv);
	initing_philosophers(&philo, &rules);
	lunching_threads(philo, rules);
	checkdeath(&rules, philo);
	return (0);
}
