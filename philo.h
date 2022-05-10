#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include "philo.h"




typedef struct s_rules
{
	int	nb_philo;
	int	time_to_die;
	int	time_to_sleep;
	int	time_to_eat;
	int number_times_to_eat;
	int dead;

}		t_rules;

typedef struct s_philosophers
{
	int			id;
	pthread_t   thread_id;
	int			left_fork;
	int			nb_eat;
	long long	timestamp;
	
	t_rules		*rules;
	struct s_philosophers	*next;
	
}		t_philo;


// void	ft_lstadd_back(t_philo **lst, t_philo *new);

t_philo	*ft_lstnew(int i, t_rules *rules);
void	initing_philosophers(t_philo **philosopher, t_rules *rules);
void	entring_arguments(t_rules *rules, char	**argv);



#endif
