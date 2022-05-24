/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 20:40:41 by sahafid           #+#    #+#             */
/*   Updated: 2022/05/13 20:40:44 by sahafid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_state(t_philo *philo, int i)
{
	if (!philo->rules->dead)
	{
		if (i == 1)
		{
			printf("%ld %d  has taken a fork\n", time_stamp() - \
			philo->rules->timestamp, philo->id);
		}
		else if (i == 2)
		{
			printf("%ld %d  is eating\n", time_stamp() - \
			philo->rules->timestamp, philo->id);
		}
		else if (i == 3)
		{
			printf("%ld %d  is sleeping\n", time_stamp() - \
			philo->rules->timestamp, philo->id);
		}
		else if (i == 4)
		{
			printf("%ld %d  is thinking\n", time_stamp() - \
			philo->rules->timestamp, philo->id);
		}
	}
}

void	philo_eats(t_philo *philo, sem_t *mutex)
{
	sem_wait(mutex);
	print_state(philo, 1);
	sem_wait(mutex);
	print_state(philo, 1);
	print_state(philo, 2);
	usleep((philo->rules->time_to_eat * 1000));
	philo->last_time_eated = time_stamp();
	philo->nb_eat += 1;
	sem_post(mutex);
	sem_post(mutex);
}

void	philo_sleeping(t_philo *philo)
{
	print_state(philo, 3);
	usleep((philo->rules->time_to_sleep * 1000));
}

void	philo_thinking(t_philo *philo)
{
	print_state(philo, 4);
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
