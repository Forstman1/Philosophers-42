/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 13:27:55 by sahafid           #+#    #+#             */
/*   Updated: 2022/05/12 13:27:58 by sahafid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_philo **philo, t_rules *rules)
{
	t_philo	*tmp;
	t_philo	*lst;
	int		i;

	lst = *philo;
	i = 1;
	while (i <= lst->rules->nb_philo)
	{
		tmp = lst->next;
		pthread_mutex_destroy(&lst->fork);
		free(lst);
		lst = NULL;
		if (tmp)
			lst = tmp;
		i++;
	}
	pthread_mutex_destroy(&rules->mutex);
}

int	ft_isspace(const char *a)
{
	return (*a == '\t'
		|| *a == '\n'
		|| *a == '\v'
		|| *a == '\f'
		|| *a == '\r'
		|| *a == ' ');
}

long long	ft_atoi(const char *str)
{
	char		*a;
	int			i;
	long long	res;
	int			sign;

	a = (char *)str;
	i = 0;
	res = 0;
	sign = 1;
	while (ft_isspace(&a[i]))
		i++;
	if (a[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (a[i] == '+')
		i++;
	while (a[i] >= '0' && a[i] <= '9')
		res = res * 10 + a[i++] - '0';
	return (res * sign);
}

int	ft_isdigit(int a)
{
	return (a >= 48 && a <= 57);
}
