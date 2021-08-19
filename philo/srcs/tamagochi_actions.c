/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tamagochi_actions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <gpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 10:47:11 by gpetit            #+#    #+#             */
/*   Updated: 2021/08/19 12:17:10 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	forks(int action, int current_ph, t_datas *data)
{
	int left;
	t_philo *ph;

	if (current_ph - 1 == 0)
		left = data->nb - 1;
	else
		left = current_ph - 1;
	ph = data->philo;
	if (pthread_mutex_lock(&ph[current_ph].mutex))
		return (ERROR);
	ph[current_ph].fork = action;
	printf("%ld Philo %d has taken a fork\n", get_time_elapsed(data), current_ph);
	if (pthread_mutex_unlock(&ph[current_ph].mutex))
		return (ERROR);
	if (pthread_mutex_lock(&ph[left].mutex))
		return (ERROR);
	ph[left].fork = action;
	printf("%ld Philo %d has taken a fork\n", get_time_elapsed(data), current_ph);
	if (pthread_mutex_unlock(&ph[current_ph].mutex))
		return (ERROR);
	return (SUCCESS);
}

void	start_eating(int current_ph, t_datas *data)
{
	printf("%ld Philo %d is eating\n", get_time_elapsed(data), current_ph);
	usleep(data->tte * 1000);
}

int	tamagochi_philo(int thread_nb, t_datas *data)
{
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
