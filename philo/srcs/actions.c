/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <gpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 10:47:11 by gpetit            #+#    #+#             */
/*   Updated: 2021/09/02 17:24:26 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	status_printer(int current_ph, char *str, t_datas *data)
{
	long	time;

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

int	start_sleeping(int current_ph, t_datas *data)
{
	if (status_printer(current_ph, "is sleeping", data))
		return (ERROR);
	if (my_usleep(data->tts, data) == ERROR)
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
	int	ret;

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
	ret = check_death_variable(data);
	if (ret)
		return (ret);
	return (SUCCESS);
}
