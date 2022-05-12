/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 15:08:45 by sahafid           #+#    #+#             */
/*   Updated: 2022/05/12 15:08:47 by sahafid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>
# include "philo.h"

typedef struct s_philosophers
{
	int						id;
	pthread_t				thread_id;
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
	long	timestamp;
	int		id_dead_philo;
}		t_rules;

t_philo		*ft_lstnew(int i, t_rules *rules);
void		initing_philosophers(t_philo **philosopher, t_rules *rules);
void		entring_arguments(t_rules *rules, char	**argv);
long		time_stamp(void);
void		philo_eats(t_philo *philo);
void		free_all(t_philo **philo);
void		philo_thinking(t_philo *philo);
void		philo_sleeping(t_philo *philo);
void		checking_arguments(char	**argv);
long long	ft_atoi(const char *str);
int			ft_isdigit(int a);
void		error(void);

#endif
