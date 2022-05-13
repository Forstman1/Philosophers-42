/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 20:40:50 by sahafid           #+#    #+#             */
/*   Updated: 2022/05/13 20:40:51 by sahafid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"


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

int	checkvalid(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == ' ')
		{
			i++;
			j++;
		}
		else if (ft_isdigit(str[i]))
			i++;
		else if ((str[i] == '+' && ft_isdigit(str[i - 1])) \
			|| (str[i] == '-' && ft_isdigit(str[i - 1])))
			return (1);
		else if ((str[i] == '+' || str[i] == '-') && ft_isdigit(str[i + 1]))
			i++;
		else
			return (1);
	}
	if (i == j)
		return (1);
	return (0);
}

int	checking_arguments(char	**argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (checkvalid(argv[i]))
			return (1);
		if (ft_atoi(argv[i]) > 2147483647 || ft_atoi(argv[i]) < 0)
			return (1);
		i++;
	}
	return (0);
}
