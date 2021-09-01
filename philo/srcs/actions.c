/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <gpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 10:47:11 by gpetit            #+#    #+#             */
/*   Updated: 2021/09/01 17:08:26 by gpetit           ###   ########.fr       */
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

int	plato_died(int current_ph, t_datas *data)
{
	long	last_meal;
	long	time;

	time = get_time_elapsed(data);
	if (time == ERROR)
		return (ERROR);
	last_meal = time - data->philo[current_ph - 1].last_dinner;
	if (last_meal >= data->ttd)
		if (kill_philo(current_ph, data))
			return (ERROR);
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

int	start_sleeping(int current_ph, t_datas *data)
{
	if (status_printer(current_ph, "is sleeping", data))
		return (ERROR);
	if (my_usleep(current_ph, data->tts, data) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	start_thinking(int current_ph, t_datas *data)
{
	if (status_printer(current_ph, "is thinking", data))
		return (ERROR);
	return (SUCCESS);
}

int	tamagochi_philo(int thread_nb, t_datas *data)
{
	if (take_forks(thread_nb, data))
		return (ERROR);
	if (start_eating(thread_nb, data))
		return (ERROR);
	if (drop_forks(thread_nb, data))
		return (ERROR);
	if (start_sleeping(thread_nb, data))
		return (ERROR);
	if (start_thinking(thread_nb, data))
		return (ERROR);
	if (plato_died(thread_nb, data))
		return (DEATH);
	return (SUCCESS);
}
