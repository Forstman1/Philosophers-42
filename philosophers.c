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


#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


typedef struct s_rules
{
	int	nb_philo;
	int	time_to_die;
	int	time_to_sleep;
	int	time_to_eat;
	int number_times_to_eat;

}  t_rules;


typedef struct s_philosopers 
{
	pthread_t philo;
	struct s_philosophers *next;
} t_philo;

void*	philosophers_state()
{
	printf("philosopher Alive\n");
	return 0;
}


void	entring_arguments(t_rules *rules, char	**argv)
{
	rules->nb_philo = atoi(argv[1]);
	rules->time_to_die = atoi(argv[2]);
	rules->time_to_eat = atoi(argv[3]);
	rules->time_to_sleep = atoi(argv[4]);
	if (argv[5] != NULL)
		rules->number_times_to_eat = atoi(argv[5]);
}

void	initing_philosophers(t_philo **philo)
{
	t_philo *lst;
	lst = *philo;
	
}

int main(int argc, char	*argv[])
{
	t_philo *philo;
	t_rules rules;
	int j;
	int i;
	
	i = 0;

	if (argc != 5 && argc != 6)
		return (write(1, "entre the correct amount of arguments", 38));
	entring_arguments(&rules, argv);
	initing_philosophers(&philo);

	// while (i < 5)
	// {
	// 	pthread_create(&t[i], NULL, &philosophers_state, NULL);
	// 	i++;
	// }
	i = 0;
	// while (i < 5)
	// {
	// 	pthread_join(t[i], NULL);
	// 	i++;
	// }
	return 0;
}
