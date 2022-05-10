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
#include <pthread.h>


void*	philosophers(void *arg)
{
	t_philo *philo;

	philo = (t_philo*)arg;
	printf("philosopher Alive : %d\n", philo->id);
	// while (lst)
	return 0;
}

void lunching_threads(t_philo *philo, t_rules rules)
{
	int i;
	t_philo *lst;

	i = 1;
	lst = philo;
	while (lst && i != lst->rules->nb_philo)
	{
		pthread_create(&(lst->thread_id), NULL, &philosophers, lst);
		lst = lst->next;
		i++;
	}
	usleep(500);
}

// void	checkdeath(t_rules *rules)
// {

// }

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
	// checkdeath(&rules);



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
