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

long	time_stamp(void)
{
	long long i;
	struct timeval current_time;
	
	gettimeofday(&current_time, NULL);
	i = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (i);
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
	pthread_mutex_init(&philo->fork, NULL);
	philo->last_time_eated = 0;
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
	else
		rules->number_times_to_eat = -1;
	rules->dead = 0;
	rules->timestamp = time_stamp();
}




void	initing_philosophers(t_philo **philosopher, t_rules *rules)
{
	t_philo *philo;
	int		i;

	philo = *philosopher;
	*philosopher = NULL;
	i = 1;
	while (i <= rules->nb_philo)
	{
		philo = ft_lstnew(i, rules);
		ft_lstadd_back(philosopher, philo);
		i++;
	}
	philo->next = *philosopher;
}