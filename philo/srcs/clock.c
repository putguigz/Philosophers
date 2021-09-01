/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clock.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <gpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 19:07:19 by gpetit            #+#    #+#             */
/*   Updated: 2021/09/01 16:31:37 by gpetit           ###   ########.fr       */
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

int	my_usleep(int current_ph, int time_needed, t_datas *data)
{
	long	starting_time;
	long	elapsed_time;
	int		ret;

	elapsed_time = 0;
	starting_time = get_time_elapsed(data);
	while (elapsed_time < time_needed)
	{
		usleep(300);
		ret = plato_died(current_ph, data);
		if (ret)
			return (ret);
		elapsed_time = get_time_elapsed(data) - starting_time;
	}
	return (SUCCESS);
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
