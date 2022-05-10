/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 18:17:53 by sahafid           #+#    #+#             */
/*   Updated: 2022/05/10 18:17:55 by sahafid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "philo.h"

void*	philosophers()
{
	printf("philosopher Alive\n");
	return 0;
}

void	ft_lstadd_back(t_philo **lst, t_philo *new)
{
	t_philo	*root;

	root = *lst;
	if (!(*lst))
		*lst = new;
	else
	{
		while (root->next != NULL)
			root = root->next;
		root->next = new;
	}
}

int		time_stamp(void)
{
	int i;

	i = gettimeofday();
}

t_philo	*ft_lstnew(int i, t_rules *rules)
{
	t_philo	*philo;

	philo = NULL;
	philo = (t_philo *)malloc(sizeof(t_philo));
	if (philo == NULL)
		return (NULL);
	philo->id = i;
	philo->rules = rules;
	philo->left_fork = i;
	if (rules->number_times_to_eat)
		philo->nb_eat = rules->number_times_to_eat;
	philo->timestamp = time_stamp();
	philo->next = NULL;
	return (philo);
}

void	entring_arguments(t_rules *rules, char	**argv)
{
	rules->nb_philo = atoi(argv[1]);
	rules->time_to_die = atoi(argv[2]);
	rules->time_to_eat = atoi(argv[3]);
	rules->time_to_sleep = atoi(argv[4]);
	if (argv[5] != NULL)
		rules->number_times_to_eat = atoi(argv[5]);
	rules->dead = 0;
}



void	initing_philosophers(t_philo **philosopher, t_rules *rules)
{
	t_philo *philo;
	int		i;

	philo = *philosopher;
	i = 1;
	while (i <= rules->nb_philo)
	{
		philo = ft_lstnew(i, rules);
		ft_lstadd_back(philosopher, philo);
		i++;
	}
}