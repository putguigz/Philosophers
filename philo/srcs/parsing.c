/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <gpetit@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 10:21:48 by gpetit              #+#    #+#             */
/*   Updated: 2021/08/09 16:50:00 by gpetit             ###   ########.fr       */
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
	if (ft_atoi(str) > INT_MAX || ft_atoi(str) < 0)
		return (ERROR);
	return (SUCCESS);
}

void	store_in_philo_struct(int i, char *str, t_datas *data)
{
	if (i == 1)
		data->nb = ft_atoi(str);
	else if (i == 2)
		data->ttd = ft_atoi(str);
	else if (i == 3)
		data->tte = ft_atoi(str);
	else if (i == 4)
		data->tts = ft_atoi(str);
	else if (i == 5)
	{
		data->meals_flag = 1;
		data->meals = ft_atoi(str);
	}
}

int	register_philo_input(char **av, t_datas *data)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (!input_conformity(av[i]))
			store_in_philo_struct(i, av[i], data);
		else
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}
