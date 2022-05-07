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

void*	philosophers_state()
{
	printf("Alive\n");
}

int main(int argc, char	*argv[])
{
	pthread_t t[3];
	int i;
	
	i = 0;
	while (i < 3)
	{
		pthread_create(&t[i], NULL, &philosophers_state, NULL);
		i++;
	}
	i = 0;
	while (i < 3)
	{
		pthread_join(t[i], NULL);
		i++;
	}

	return 0;
}