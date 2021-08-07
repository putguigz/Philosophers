/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 10:21:48 by user              #+#    #+#             */
/*   Updated: 2021/08/07 19:24:35 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	input_conformity(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (ERROR);
		i++;
	}
	if (ft_atoi(str) > INT32_MAX || ft_atoi(str) < 0)
		return (ERROR);
	return (SUCCESS);
}

void	store_in_philo_struct(int i, char *str, t_philo *philo)
{
	if (i == 1)
		philo->nb = ft_atoi(str);
	else if (i == 2)
		philo->ttd = ft_atoi(str);
	else if (i == 3)
		philo->tte = ft_atoi(str);
	else if (i == 4)
		philo->tts = ft_atoi(str);
	else if (i == 5)
	{
		philo->meals_flag = 1;
		philo->meals = ft_atoi(str);
	}
}

int	register_philo_input(char **av, t_philo *philo)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (!input_conformity(av[i]))
			store_in_philo_struct(i, av[i], philo);
		else
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}
