/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 13:37:02 by user              #+#    #+#             */
/*   Updated: 2021/08/09 16:51:44 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_fork_to_usable(t_philo *philo, int elems)
{
	int	i;

	i = 0;
	while (i < elems)
	{
		philo[i].nb = i + 1;
		philo[i].fork = 1;
		i++;
	}
}

t_philo	*create_philo_give_them_forks(t_datas *data)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo) * data->nb);
	if (!philo)
		return (NULL);
	memset(philo, 0, sizeof(philo) * data->nb);
	set_fork_to_usable(philo, data->nb);
	return (philo);
}

int	start_vandevilling(t_datas *data)
{
	t_philo	*philo;

	if (gettimeofday(&(data->time), NULL))
		return (ERROR);
	philo = create_philo_give_them_forks(data);
	if (!philo)
		return (ERROR);
	free(philo);
	return (SUCCESS);
}
