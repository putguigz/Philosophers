/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <gpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 15:29:34 by gpetit            #+#    #+#             */
/*   Updated: 2021/08/19 15:43:04 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *elem)
{
	t_philo *philo;

	philo = (t_philo *)elem;
	if (philo->nb % 2 == 0)
		usleep(1000);
	tamagochi_philo(philo->nb, philo->data);
	return (elem);
}

int	launch_threads(t_datas *data)
{
	int i;
	static int ret_status = SUCCESS;
	pthread_t *thread;

	i = 0;
	thread = (pthread_t *)malloc(sizeof(pthread_t) * data->nb);
	if (!thread || pthread_mutex_init(&data->mutex, NULL))
		ret_status = ERROR;
	while (!ret_status && i < data->nb)
	{
		if (pthread_create(thread + i, NULL, &routine, data->philo + i)) //CONTROLER RETOUR DE &ROUTINE
			ret_status = ERROR;
		i++;
	}
	i = 0;
	while (!ret_status && i < data->nb)
	{
		if (pthread_join(thread[i], NULL))
			ret_status = ERROR;
		i++;
	}
	if (thread)
		free(thread);
	return (ret_status);
}
