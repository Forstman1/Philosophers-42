/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 14:21:10 by sahafid           #+#    #+#             */
/*   Updated: 2022/05/12 14:21:11 by sahafid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error(void)
{
	write(1, "ERROR ON THE ARGUMENTS\n", 24);
	exit(0);
}

void	checkvalid(char *str)
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
			error();
		else if ((str[i] == '+' || str[i] == '-') && ft_isdigit(str[i + 1]))
			i++;
		else
			error();
	}
	if (i == j)
		error();
}

void	checking_arguments(char	**argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		checkvalid(argv[i]);
		if (ft_atoi(argv[i]) >= 2147483647 || ft_atoi(argv[i]) < 1)
			error();
		i++;
	}
}
