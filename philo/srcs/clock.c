/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clock.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 19:07:19 by user              #+#    #+#             */
/*   Updated: 2021/08/09 16:02:53 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
