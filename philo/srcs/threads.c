/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <gpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 15:29:34 by gpetit            #+#    #+#             */
/*   Updated: 2021/08/13 20:46:06 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *elem)
{
/* 	t_datas *data;

	data = (t_datas *)elem; */
	printf("Bonjour je suis le philosophe numéro : %d\n", *((int *)elem));
	free(elem);
	return (elem);
}

int	launch_threads(t_datas *data)
{
	int i;
	pthread_t *thread;

	i = 0;
	thread = (pthread_t *)malloc(sizeof(pthread_t) * data->nb);
	if (!thread)
		return (ERROR);
	while (i < data->nb)
	{
		int *nb = malloc(sizeof(int));
		*nb = i;
		pthread_create(thread + i, NULL, &routine, nb); //PROTEGER
		i++;
	}
	i = 0;
	while (i < data->nb)
	{
		pthread_join(thread[i], NULL); //PROTEGER
		i++;
	}
	return (SUCCESS);
}
