/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <gpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 15:03:00 by gpetit            #+#    #+#             */
/*   Updated: 2021/09/02 19:09:48 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	increase_count(int *count, t_philo philo, t_datas *data)
{
	if (pthread_mutex_lock(&philo.meals_mutex))
		return (ERROR);
	if (philo.meal >= data->meals)
		(*count)++;
	if (pthread_mutex_unlock(&philo.meals_mutex))
		return (ERROR);
	return (SUCCESS);
}

int	are_you_guys_done(t_philo *philo)
{
	t_datas	*data;
	int		i;
	int		count;

	i = 0;
	count = 0;
	data = philo->data;
	while (i < data->nb)
	{
		if (increase_count(&count, philo[i], data))
			return (ERROR);
		i++;
	}
	if (count == data->nb)
	{
		if (pthread_mutex_lock(&data->death_mutex))
			return (ERROR);
		data->death = DEATH;
		if (pthread_mutex_unlock(&data->death_mutex))
			return (ERROR);
	}
	return (SUCCESS);
}

int	drop_forks(int current_ph, t_datas *data)
{
	int		left;
	int		index;
	t_philo	*ph;

	ph = data->philo;
	left = set_left_philo(&index, current_ph, data);
	ph[index].fork = 1;
	if (pthread_mutex_unlock(&ph[index].mutex))
		return (ERROR);
	if (left != -1)
	{	
		ph[left].fork = 1;
		if (pthread_mutex_unlock(&ph[left].mutex))
			return (ERROR);
	}
	return (SUCCESS);
}

int	start_eating(int current_ph, t_datas *data)
{
	long	time;

	time = get_time_elapsed(data);
	if (time == ERROR)
		return (ERROR);
	if (pthread_mutex_lock(&data->philo[current_ph - 1].dinner_mutex))
		return (ERROR);
	data->philo[current_ph - 1].last_dinner = time;
	if (pthread_mutex_unlock(&data->philo[current_ph - 1].dinner_mutex))
		return (ERROR);
	if (status_printer(current_ph, "is eating", data))
		return (ERROR);
	if (my_usleep(data->tte, data) == ERROR)
		return (ERROR);
	if (data->meals_flag)
	{
		if (pthread_mutex_lock(&data->philo[current_ph - 1].meals_mutex))
			return (ERROR);
		data->philo[current_ph - 1].meal++;
		if (pthread_mutex_unlock(&data->philo[current_ph - 1].meals_mutex))
			return (ERROR);
		if (are_you_guys_done(data->philo))
			return (ERROR);
	}
	return (SUCCESS);
}

int	take_forks(int current_ph, t_datas *data)
{
	int		left;
	int		index;
	t_philo	*ph;

	ph = data->philo;
	left = set_left_philo(&index, current_ph, data);
	if (pthread_mutex_lock(&ph[index].mutex))
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
		if (my_usleep(data->ttd, data) == ERROR)
			return (ERROR);
	return (SUCCESS);
}
