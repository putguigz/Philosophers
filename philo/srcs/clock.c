/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clock.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <gpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 19:07:19 by gpetit            #+#    #+#             */
/*   Updated: 2021/08/19 09:53:43 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	usleep_chronometer(void)
{
	struct timeval	time;
	long			elapsed;

	if (gettimeofday(&time, NULL))
		return (ERROR);
	elapsed = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (elapsed);
}

void	my_usleep(int time_needed)
{
	long	starting_time;
	long	elapsed_time;

	elapsed_time = 0;
	starting_time = usleep_chronometer();
	while (elapsed_time < time_needed)
	{
		usleep(time_needed / 10);
		elapsed_time = usleep_chronometer() - starting_time;
	}
}

long	get_time_elapsed(t_datas *data)
{
	struct timeval	time;
	long			elapsed;

	if (gettimeofday(&time, NULL))
		return (ERROR);
	elapsed = ((time.tv_sec - data->time.tv_sec) * 1000 + \
	(time.tv_usec - data->time.tv_usec) / 1000);
	return (elapsed);
}
