/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tamagochi_actions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <gpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 10:47:11 by gpetit            #+#    #+#             */
/*   Updated: 2021/08/30 23:39:34 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	status_printer(int current_ph, char *str, t_datas *data)
{
	long time;

	time = get_time_elapsed(data);
	if (time == ERROR)
		return (ERROR);
	if (pthread_mutex_lock(&data->death_mutex))
		return (ERROR);
	if (!data->death)
	{
		printf("%ld Philo_%d", time, current_ph);
		printf(" %s\n", str);
	}
	if (pthread_mutex_unlock(&data->death_mutex))
		return (ERROR);
	return (SUCCESS);
}

int	set_left_philo(int *index, int current_ph, t_datas *data)
{
	int left;

	*index = current_ph - 1;
	if (*index == 0 && data->nb != 1)
		left = data->nb - 1;
	else if (*index == 0 && data->nb == 1)
		left = -1;
	else
		left = *index - 1;
	return (left);
}

int	drop_forks(int current_ph, t_datas *data)
{
	int left;
	int	index;
	t_philo *ph;

	ph = data->philo;
	left = set_left_philo(&index, current_ph, data);
	ph[index].fork = 1;
	ph[left].fork = 1;
	pthread_mutex_unlock(&ph[index].mutex);
	pthread_mutex_unlock(&ph[left].mutex);
	return (SUCCESS);
}

int	take_forks(int current_ph, t_datas *data)
{
	int		left;
	int		index;
	t_philo	*ph;

	ph = data->philo;
	left = set_left_philo(&index, current_ph, data);
	if (!pthread_mutex_lock(&ph[index].mutex))
		return (ERROR);
	ph[index].fork = 0;
	if (status_printer(current_ph, "has taken a fork", data))
		return (ERROR);
	if (left != -1)
	{
		if (pthread_mutex_lock(&ph[left].mutex))
			return (ERROR);
		ph[left].fork = 0;
		if (status_printer(current_ph, "has taken a fork", data))
			return (ERROR);
	}
	else
		my_usleep(current_ph, data->ttd, data);
	return (SUCCESS);
}

int	kill_philo(int current_ph, t_datas *data)
{
	long time;

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
	long last_meal;
	long time;

	time = get_time_elapsed(data);
	if (time == ERROR)
		return (ERROR);
	last_meal = time - data->philo[current_ph - 1].last_dinner;
	if (last_meal >= data->ttd)
		kill_philo(current_ph, data);
	pthread_mutex_lock(&data->death_mutex);
	if (data->death == DEATH)
	{
		pthread_mutex_unlock(&data->death_mutex);
		return (DEATH);
	}
	pthread_mutex_unlock(&data->death_mutex);
	return (ALIVE);
}

void	are_you_guys_done(t_philo *philo)
{
	t_datas *data;
	int i;
	int count;

	i = 0;
	count = 0;
	data = philo->data;
	while (i < data->nb)
	{
		if (philo[i].meal >= data->meals)
			count++;
		i++;
	}
	if (count == data->nb)
	{
		pthread_mutex_lock(&data->death_mutex);
		data->death = DEATH;
		pthread_mutex_unlock(&data->death_mutex);
	}
}

int	start_eating(int current_ph, t_datas *data)
{
	long	time;

	time = get_time_elapsed(data);
	if (time == ERROR)
		return (ERROR);
	data->philo[current_ph - 1].last_dinner = time;
	if (status_printer(current_ph, "is eating", data))
		return (ERROR);
	my_usleep(current_ph, data->tte, data);
	if (data->meals_flag)
	{
		data->philo[current_ph - 1].meal++;
		are_you_guys_done(data->philo);
	}
	return (SUCCESS);
}

int	start_sleeping(int current_ph, t_datas *data)
{
	if (status_printer(current_ph, "is sleeping", data))
		return (ERROR);
	my_usleep(current_ph, data->tts, data);
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
	return(SUCCESS);
}
