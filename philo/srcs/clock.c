/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clock.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 19:07:19 by user              #+#    #+#             */
/*   Updated: 2021/08/07 19:25:42 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_elapsed(t_philo *philo)
{
	struct timeval	time;
	long			elapsed;

	if (gettimeofday(&time, NULL))
		return (ERROR);
	elapsed = ((time.tv_sec - philo->time.tv_sec) * 1000 + \
	(time.tv_usec - philo->time.tv_usec) / 1000);
	return (elapsed);
}
