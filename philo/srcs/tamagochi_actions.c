/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tamagochi_actions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <gpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 10:47:11 by gpetit            #+#    #+#             */
/*   Updated: 2021/08/19 17:09:20 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	forks(int action, int current_ph, t_datas *data)
{
	int left;
	int	index;
	t_philo *ph;

	index = current_ph - 1;
	if (index == 0)
		left = data->nb - 1;
	else
		left = index - 1;
	ph = data->philo;
	if (pthread_mutex_lock(&ph[index].mutex))
		return (ERROR);
	ph[index].fork = action;
	if (!action)
		printf("%ld Philo_%d has taken a fork\n", get_time_elapsed(data), current_ph);
	if (pthread_mutex_unlock(&ph[index].mutex))
		return (ERROR);
	if (pthread_mutex_lock(&ph[left].mutex))
		return (ERROR);
	ph[left].fork = action;
	if (!action)
		printf("%ld Philo_%d has taken a fork\n", get_time_elapsed(data), current_ph);
	if (pthread_mutex_unlock(&ph[left].mutex))
		return (ERROR);
	return (SUCCESS);
}

void	start_eating(int current_ph, t_datas *data)
{
	printf("%ld Philo_%d is eating\n", get_time_elapsed(data), current_ph);
	usleep(data->tte * 1000);
	data->philo[current_ph - 1].last_dinner = get_time_elapsed(data);
}

int	tamagochi_philo(int thread_nb, t_datas *data)
{
/* 	if (thread_nb % 2 == 0)
		usleep(data->tte / 10); */
 	if (forks(0, thread_nb, data)) //FORK PICKING
		return (ERROR);
	start_eating(thread_nb, data);
	if (forks(1, thread_nb, data)) //FORK DROPPING
		return (ERROR);
/* 	drop_fork;
	start_sleeping;
	start_thinking; */
	return(SUCCESS);
}
