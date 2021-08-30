/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tamagochi_actions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <gpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 10:47:11 by gpetit            #+#    #+#             */
/*   Updated: 2021/08/30 18:50:56 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	plato_died(t_datas *data);

int	set_left_philo(int *index, int current_ph, t_datas *data)
{
	int left;

	*index = current_ph - 1;
	if (*index == 0)
		left = data->nb - 1;
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
	long	time;
	int		left;
	int		index;
	t_philo	*ph;

	ph = data->philo;
	left = set_left_philo(&index, current_ph, data);
	if (pthread_mutex_lock(&ph[index].mutex))
		return (ERROR);
	if (pthread_mutex_lock(&ph[left].mutex))
		return (ERROR);
	ph[index].fork = 0;
	time = get_time_elapsed(data);
	if (time == ERROR)
		return (ERROR);
	pthread_mutex_lock(&data->death_mutex);
	if (!data->death)
		printf("%ld Philo_%d has taken a fork\n", time, current_ph);
	pthread_mutex_unlock(&data->death_mutex);
	ph[left].fork = 0;
	time = get_time_elapsed(data);
	if (time == ERROR)
		return (ERROR);
	pthread_mutex_lock(&data->death_mutex);
	if (!data->death)
		printf("%ld Philo_%d has taken a fork\n", time, current_ph);
	pthread_mutex_unlock(&data->death_mutex);
	return (SUCCESS);
}

int	kill_philo(int current_ph, t_datas *data)
{
	long time;

	pthread_mutex_lock(&data->death_mutex);
	data->death = DEATH;
	time = get_time_elapsed(data);
	if (time == ERROR)
		return (ERROR);
	printf("%ld Philo_%d died\n", time, current_ph);
	pthread_mutex_unlock(&data->death_mutex);
	return (SUCCESS);
}

int	plato_died(t_datas *data)
{
	pthread_mutex_lock(&data->death_mutex);
	if (data->death == DEATH)
	{
		pthread_mutex_unlock(&data->death_mutex);
		return (DEATH);
	}
	pthread_mutex_unlock(&data->death_mutex);
	return (ALIVE);
}

int	start_eating(int current_ph, t_datas *data)
{
	long	time;
	long	last_meal;

	time = get_time_elapsed(data);
	if (time == ERROR)
		return (ERROR);
	last_meal = time - data->philo[current_ph - 1].last_dinner;
	data->philo[current_ph - 1].last_dinner = time;
	if (last_meal > data->ttd)
		return (kill_philo(current_ph, data));
	pthread_mutex_lock(&data->death_mutex);
	if (!data->death)
		printf("%ld Philo_%d is eating\n", time, current_ph);
	pthread_mutex_unlock(&data->death_mutex);
	my_usleep(data->tte);
	//RAJOUTER VERIFICATION DU NOMBRE DE REPAS ICI
	return (SUCCESS);
}

int	start_sleeping(int current_ph, t_datas *data)
{
	long time;

	time = get_time_elapsed(data);
	if (time == ERROR)
		return (ERROR);
	pthread_mutex_lock(&data->death_mutex);
	if (!data->death)
		printf("%ld Philo_%d is sleeping\n", time, current_ph);
	pthread_mutex_unlock(&data->death_mutex);
	my_usleep(data->tts);
	return (SUCCESS);
}

int	start_thinking(int current_ph, t_datas *data)
{
	long time;

	time = get_time_elapsed(data);
	if (time == ERROR)
		return (ERROR);
	pthread_mutex_lock(&data->death_mutex);
	if (!data->death)
		printf("%ld Philo_%d is thinking\n", time, current_ph);
	pthread_mutex_unlock(&data->death_mutex);
	return (SUCCESS);
}

int	tamagochi_philo(int thread_nb, t_datas *data)
{
 	if (take_forks(thread_nb, data))
		return (ERROR);
	if (plato_died(data))
		return (DEATH);	
	if (start_eating(thread_nb, data))
		return (ERROR);
	if (drop_forks(thread_nb, data))
		return (ERROR);
	if (plato_died(data))
		return (DEATH);
	if (start_sleeping(thread_nb, data))
		return (ERROR);
	if (plato_died(data))
		return (DEATH);
	if (start_thinking(thread_nb, data))
		return (ERROR);
	if (plato_died(data))
		return (DEATH);
	return(SUCCESS);
}
