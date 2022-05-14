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
		// sleep(1);
		philo->rules->dead = 1;
	}
	return (0);
}

void	p_thread(t_philo *philo)
{
	t_philo *lst;

	lst = philo;
	lst->last_time_eated = time_stamp();
	// pthread_create(&(lst->thread_id), NULL, &philosophers, lst);
	while (!philo->rules->dead)
		philosophers((void*)lst);
	exit(1);
}

int	lunching_threads(t_philo *philo, t_rules rules)
{
	int		i;
	t_philo	*lst;
	int		id;

	i = 1;
	id = 1;
	lst = philo;
	if (!lst)
		return (1);
	while (lst && i <= lst->rules->nb_philo)
	{
		lst->thread_id = fork();
		if (lst->thread_id < 0)
			exit(0);
		else if (lst->thread_id == 0)
			p_thread(lst);	
		i++;
		lst = lst->next;
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
	lunching_threads(*philo, *rules);
	while (1)
	{
		printf("%d\n", (*philo)->rules->dead);
		if ((*philo)->rules->dead == 1)
			printf("ana hna\n");
		sleep(2);	
		usleep(1000);
	}
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