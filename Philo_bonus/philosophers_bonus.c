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

void	*checkdeath(void	*lst)
{
	t_philo	*philo;

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
			exit(1);
		usleep(500);
	}
	return (0);
}

void	philosophers(t_philo *philo, sem_t *mutex)
{
	if (philo->id % 2)
		usleep(200);
	while (!(philo->rules->dead))
	{
		philo_eats(philo, mutex);
		philo_sleeping(philo);
		philo_thinking(philo);
	}
	sem_close(mutex);
}

void	p_thread(t_philo *philo, sem_t *mutex)
{
	philo->last_time_eated = time_stamp();
	pthread_create(&(philo->thread_id), NULL, (void *)checkdeath, \
	(void *)philo);
	while (!philo->rules->dead)
		philosophers(philo, mutex);
	if (philo->done_eating == 1)
		exit(0);
	exit(1);
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
	checksituation(*philo);
	free_all(philo, (*philo)->rules);
	sem_unlink("mutex");
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
	return (0);
}
