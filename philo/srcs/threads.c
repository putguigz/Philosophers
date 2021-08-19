/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <gpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 15:29:34 by gpetit            #+#    #+#             */
/*   Updated: 2021/08/19 12:07:41 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *elem)
{
	t_datas *data;

	static int i = 0;

	data = (t_datas *)elem;
	pthread_mutex_lock(&data->mutex);
	i++;
	pthread_mutex_unlock(&data->mutex);
	tamagochi_philo(i, data);
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
		if (pthread_create(thread + i, NULL, &routine, data)) //CONTROLER RETOUR DE &ROUTINE
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
