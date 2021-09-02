/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <gpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 14:27:03 by gpetit            #+#    #+#             */
/*   Updated: 2021/09/02 19:11:15 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	kill_philo(int current_ph, t_datas *data)
{
	long	time;

	if (pthread_mutex_lock(&data->death_mutex))
		return (ERROR);
	if (data->death == ALIVE)
	{	
		data->death = DEATH;
		time = get_time_elapsed(data);
		if (time == ERROR)
			return (ERROR);
		printf("%ld Philo_%d died\n", time, current_ph);
	}
	if (pthread_mutex_unlock(&data->death_mutex))
		return (ERROR);
	return (SUCCESS);
}

int	check_death_variable(t_datas *data)
{
	if (pthread_mutex_lock(&data->death_mutex))
		return (ERROR);
	if (data->death == DEATH)
	{
		if (pthread_mutex_unlock(&data->death_mutex))
			return (ERROR);
		return (DEATH);
	}
	if (pthread_mutex_unlock(&data->death_mutex))
		return (ERROR);
	return (ALIVE);
}

int	did_anyone_die(int current_ph, t_datas *data)
{
	long	last_meal;
	long	time;

	time = get_time_elapsed(data);
	if (time == ERROR)
		return (ERROR);
	if (pthread_mutex_lock(&data->philo[current_ph - 1].dinner_mutex))
		return (ERROR);
	last_meal = time - data->philo[current_ph - 1].last_dinner;
	if (pthread_mutex_unlock(&data->philo[current_ph - 1].dinner_mutex))
		return (ERROR);
	if (last_meal >= data->ttd)
		if (kill_philo(current_ph, data))
			return (ERROR);
	return (check_death_variable(data));
}

int	monitor_everyone(t_datas *data)
{
	int		i;
	int		ret;

	ret = ALIVE;
	while (1)
	{
		i = -1;
		while (++i < data->nb && ret == ALIVE)
			ret = did_anyone_die(i + 1, data);
		if (ret)
			return (ret);
		usleep(300);
	}
	return (SUCCESS);
}
