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


void	philo_eats(t_philo *philo)
{
	t_philo *right_fork;


	right_fork = philo->next;
	pthread_mutex_lock(&philo->fork);
	printf("%ld %d  has taken a fork\n", time_stamp() - philo->rules->timestamp, philo->id);
	pthread_mutex_lock(&right_fork->fork);
	printf("%ld %d  has taken a fork\n", time_stamp() - philo->rules->timestamp, philo->id);
	printf("%ld %d  is eating\n", time_stamp() - philo->rules->timestamp, philo->id);
	philo->last_time_eated = time_stamp();
	usleep((philo->rules->time_to_eat * 1000));
	philo->nb_eat += 1;
	if (philo->rules->number_times_to_eat == philo->nb_eat)
		philo->rules->philo_eated++;
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&right_fork->fork);
}

void	philo_sleeping(t_philo *philo)
{
	printf("%ld %d  is sleeping\n", time_stamp() - philo->rules->timestamp, philo->id);
	usleep((philo->rules->time_to_sleep * 1000));
}

void	philo_thinking(t_philo *philo)
{
	printf("%ld %d  is thinking\n", time_stamp() - philo->rules->timestamp, philo->id);
}

void*	philosophers(void *arg)
{
	t_philo *philo;

	philo = (t_philo*)arg;
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

void lunching_threads(t_philo *philo, t_rules rules)
{
	int i;
	t_philo *lst;

	i = 1;
	lst = philo;
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
			printf("philosopher : %d is dead\n", philo->id);
			philo->rules->dead = 1;
			return ;
		}
		usleep(500);
	}
}

int main(int argc, char	*argv[])
{
	t_rules rules;
	t_philo *philo;
	int j;
	int i;
	
	i = 0;

	if (argc != 5 && argc != 6)
		return (write(1, "entre the correct amount of arguments", 38));
	entring_arguments(&rules, argv);
	initing_philosophers(&philo, &rules);
	lunching_threads(philo, rules);
	checkdeath(&rules, philo);
	



	// while (i < 5)
	// {
	// 	pthread_create(&t[i], NULL, &philosophers_state, NULL);
	// 	i++;
	// }
	// while (i < 5)
	// {
	// 	pthread_join(t[i], NULL);
	// 	i++;
	// }
	return 0;
}
