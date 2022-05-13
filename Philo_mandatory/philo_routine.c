/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 13:26:17 by sahafid           #+#    #+#             */
/*   Updated: 2022/05/12 13:26:18 by sahafid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_state(t_philo *philo, int i)
{
	pthread_mutex_lock(&philo->rules->mutex);
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
	pthread_mutex_unlock(&philo->rules->mutex);
}

void	philo_eats(t_philo *philo)
{
	t_philo	*right_fork;

	right_fork = philo->next;
	pthread_mutex_lock(&philo->fork);
	print_state(philo, 1);
	pthread_mutex_lock(&right_fork->fork);
	print_state(philo, 1);
	print_state(philo, 2);
	usleep((philo->rules->time_to_eat * 1000));
	philo->last_time_eated = time_stamp();
	philo->nb_eat += 1;
	if (philo->rules->number_times_to_eat == philo->nb_eat)
		philo->rules->philo_eated++;
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&right_fork->fork);
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
