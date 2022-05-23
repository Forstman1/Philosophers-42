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

void	philosophers(t_philo *philo, sem_t *mutex)
{
	
	if (philo->id % 2)
		usleep(200);
	while (!(philo->rules->dead))
	{
		// printf("%ld ===========\n", philo->last_time_eated);
		philo_eats(philo, mutex);
		philo_sleeping(philo);
		philo_thinking(philo);
	}
}

void	*checkdeath(void	*lst)
{
	t_philo *philo;

	philo = (t_philo *)lst;
	while (1)
	{
		if (philo->nb_eat == philo->rules->number_times_to_eat)
		{
			philo->rules->dead = 1;
			philo->done_eating = 1;
			return (0);
		}
		if (time_stamp() - philo->last_time_eated > philo->rules->time_to_die)
			exit(0);
		usleep(50000);
	}
	return (0);
}

void	p_thread(t_philo *philo, sem_t *mutex)
{
	// t_philo *lst;

	// lst = philo;
	philo->last_time_eated = time_stamp();
	pthread_create(&(philo->thread_id), NULL, (void*)checkdeath, (void *)philo);
	pthread_detach(philo->thread_id);
	while (!philo->rules->dead)
		philosophers(philo, mutex);
	if (philo->done_eating)
		exit(1);
	exit(0);
}

int	lunching_threads(t_philo *philo, t_rules rules)
{
	int		i;
	t_philo	*lst;
	int		id;
	sem_t	*mutex;

	i = 1;
	id = 1;
	lst = philo;
	sem_unlink("mutex");
	mutex = sem_open("mutex", O_CREAT, 666, rules.nb_philo);
	if (!lst)
		return (1);
	while (lst && i <= lst->rules->nb_philo)
	{
		lst->process_id = fork();
		if (lst->process_id < 0)
			exit(0);
		else if (lst->process_id == 0)
			p_thread(lst, mutex);
		i++;
		lst = lst->next;
	}
	return (0);
}


int	all_functions(t_philo **philo, t_rules *rules, char **argv)
{
	int test;
	int	i;
	t_philo *lst;

	test = 0;
	i = 0;
	if (checking_arguments(argv))
		return (1);
	if (entring_arguments(rules, argv))
		return (1);
	if (initing_philosophers(philo, rules))
		return (1);
	lunching_threads(*philo, *rules);
	lst = *philo;
	while (i < rules->nb_philo)
	{
		waitpid(-1, &test, 0);
		if (test != 0)
		{
			i = 1;
			while (i <= rules->nb_philo)
			{
				kill(lst->process_id, 15);
				lst = lst->next;
				i++;
			}
			printf("philo is dead\n");
			break ;
		}
		i++;
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