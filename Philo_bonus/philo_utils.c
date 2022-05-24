/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 20:58:14 by sahafid           #+#    #+#             */
/*   Updated: 2022/05/13 20:58:15 by sahafid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_philo	*ft_lstnew(int i, t_rules *rules)
{
	t_philo	*philo;

	philo = NULL;
	philo = (t_philo *)malloc(sizeof(t_philo));
	if (philo == NULL)
		return (NULL);
	philo->id = i;
	philo->rules = rules;
	philo->last_time_eated = 0;
	philo->nb_eat = 0;
	philo->done_eating = 0;
	philo->next = NULL;
	return (philo);
}

void	ft_lstadd_back(t_philo **lst, t_philo *new)
{
	t_philo	*root;

	root = *lst;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	else
	{
		while (root->next != NULL)
			root = root->next;
		root->next = new;
	}
}

int	initing_philosophers(t_philo **philosopher, t_rules *rules)
{
	t_philo	*philo;
	int		i;

	philo = *philosopher;
	*philosopher = NULL;
	i = 1;
	if (rules->nb_philo <= 0)
		return (1);
	while (i <= rules->nb_philo)
	{
		philo = ft_lstnew(i, rules);
		ft_lstadd_back(philosopher, philo);
		i++;
	}
	philo->next = *philosopher;
	return (0);
}

long	time_stamp(void)
{
	long long		i;
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	i = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (i);
}

int	entring_arguments(t_rules *rules, char	**argv)
{
	rules->nb_philo = ft_atoi(argv[1]);
	if (rules->nb_philo == 0)
		return (1);
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5] != NULL)
	{
		rules->number_times_to_eat = ft_atoi(argv[5]);
		if (rules->number_times_to_eat == 0)
			return (1);
	}
	else
		rules->number_times_to_eat = -1;
	rules->dead = 0;
	rules->timestamp = time_stamp();
	return (0);
}
