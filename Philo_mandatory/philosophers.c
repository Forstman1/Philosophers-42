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

int	lunching_threads(t_philo *philo)
{
	int		i;
	t_philo	*lst;

	i = 1;
	lst = philo;
	if (!lst)
		return (1);
	while (lst && i <= lst->rules->nb_philo)
	{
		pthread_create(&(lst->thread_id), NULL, &philosophers, lst);
		lst->last_time_eated = time_stamp();
		lst = lst->next;
		i++;
	}
	return (0);
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
			philo->rules->dead = 1;
			usleep(200);
			pthread_mutex_lock(&(philo->rules->mutex));
			printf("%ld philosopher  %d is dead\n", time_stamp() - \
			philo->last_time_eated, philo->id);
			pthread_mutex_unlock(&(philo->rules->mutex));
			return ;
		}
		philo = philo->next;
		usleep(500);
	}
}

int	all_functions(t_philo **philo, t_rules *rules, char **argv)
{
	if (checking_arguments(argv))
		return (1);
	if (entring_arguments(rules, argv))
		return (1);
	if (initing_philosophers(philo, rules))
	{
		free_all(philo, rules);
		return (1);
	}
	if (lunching_threads(*philo))
		return (1);
	return (0);
}

int	main(int argc, char	*argv[])
{
	t_rules	rules;
	t_philo	*philo;
	int		i;

	i = 0;
	if (argc != 5 && argc != 6)
		return (write(2, "entre the correct amount of arguments\n", 39));
	if (all_functions(&philo, &rules, argv))
		return (write(2, "ERROR ON THE ARGUMENTS\n", 24));
	checkdeath(&rules, philo);
	free_all(&philo, &rules);
	return (0);
}
