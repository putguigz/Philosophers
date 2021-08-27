/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tamagochi_actions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <gpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 10:47:11 by gpetit            #+#    #+#             */
/*   Updated: 2021/08/19 17:09:20 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	pthread_mutex_unlock(&ph[index].mutex); //CONTROLLER MUTEX
	pthread_mutex_unlock(&ph[left].mutex); //CONTROLLER MUTEX
	return (SUCCESS);
}

int	take_forks(int current_ph, t_datas *data)
{
	int left;
	int	index;
	t_philo *ph;

	ph = data->philo;
	left = set_left_philo(&index, current_ph, data);
	pthread_mutex_lock(&ph[index].mutex); //CONTROLLER MUTEX
	pthread_mutex_lock(&ph[left].mutex); //CONTROLLER MUTEX
	ph[index].fork = 0;
	printf("%ld Philo_%d has taken a fork\n", get_time_elapsed(data), current_ph); //CONTROLLER RETOUR GET_TIME
	ph[left].fork = 0;
	printf("%ld Philo_%d has taken a fork\n", get_time_elapsed(data), current_ph); //CONTROLLER RETOUR GET_TIME
	return (SUCCESS);
}

void	start_eating(int current_ph, t_datas *data)
{
	printf("%ld Philo_%d is eating\n", get_time_elapsed(data), current_ph); //CONTROLLER RETOUR GET_TIME
	usleep(data->tte * 1000);
	data->philo[current_ph - 1].last_dinner = get_time_elapsed(data); //CONTROLLER RETOUR GET_TIME
}

void	start_sleeping(int current_ph, t_datas *data)
{
	printf("%ld Philo_%d is sleeping\n", get_time_elapsed(data), current_ph); //CONTROLLER RETOUR GET_TIME
	usleep(data->tts * 1000);
}

void	start_thinking(int current_ph, t_datas *data)
{
	printf("%ld Philo_%d is thinking\n", get_time_elapsed(data), current_ph); //CONTROLLER RETOUR GET_TIME
}

int	tamagochi_philo(int thread_nb, t_datas *data)
{
 	if (take_forks(thread_nb, data))
		return (ERROR);
	start_eating(thread_nb, data);
	if (drop_forks(thread_nb, data))
		return (ERROR);
	start_sleeping(thread_nb, data);
	start_thinking(thread_nb, data);
	return(SUCCESS);
}
