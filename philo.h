#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include "philo.h"


typedef struct s_philosophers
{
	int						id;
	pthread_t  				thread_id;
	pthread_mutex_t			fork;
	int						nb_eat;
	long					last_time_eated;
	struct s_rules			*rules;
	struct s_philosophers	*next;
	
}		t_philo;

typedef struct s_rules
{
	int		nb_philo;
	int		time_to_die;
	int		time_to_sleep;
	int		time_to_eat;
	int		number_times_to_eat;
	int		dead;
	int		philo_eated;
	t_philo	*philo;
	long	timestamp;

}		t_rules;




t_philo	*ft_lstnew(int i, t_rules *rules);
void	initing_philosophers(t_philo **philosopher, t_rules *rules);
void	entring_arguments(t_rules *rules, char	**argv);
long		time_stamp(void);



#endif
