/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <gpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 15:48:05 by gpetit            #+#    #+#             */
/*   Updated: 2021/08/13 20:28:07 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo/includes/philo.h"

void	*routine(void *nb)
{
	printf("Hello world from thread Number %d\n", *((int *)nb));
	free(nb);
	pthread_exit(NULL);
}

int	main(void)
{
	int i;
	pthread_t thread[5];

	for(i = 0; i < 5; i++)
	{
		int *nb = malloc(sizeof(int));
		*nb = i;
		if (pthread_create(thread + i, NULL, &routine, nb))
			return (ERROR);
	}
	for(i = 0; i < 5; i++)
	{
		pthread_join(thread[i], NULL);
	}
	return (SUCCESS);
}
