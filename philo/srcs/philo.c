/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 13:37:02 by user              #+#    #+#             */
/*   Updated: 2021/08/07 19:24:56 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_vandevilling(t_philo *philo)
{
	long	time;

	if (gettimeofday(&(philo->time), NULL))
		return (ERROR);
	time = get_time_elapsed(philo);
	printf("time elapsed since start of program = %ld\n", time);
	usleep(132392);
	time = get_time_elapsed(philo);
	printf("time elapsed since start of program = %ld\n", time);
	return (SUCCESS);
}
