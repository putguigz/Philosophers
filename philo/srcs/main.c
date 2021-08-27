/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <gpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 17:33:39 by gpetit            #+#    #+#             */
/*   Updated: 2021/08/19 10:18:29 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_datas_struct(t_datas *data)
{
	data->nb = 0;
	data->ttd = 0;
	data->tte = 0;
	data->tts = 0;
	data->meals_flag = 0;
	data->meals = 0;
	data->death = 0;
	data->philo = NULL;
}

int	main(int ac, char **av)
{
	t_datas	data;

	if (ac != 5 && ac != 6)
	{
		ft_putstr_fd("Wrong number of arguments\n", 2);
		return (0);
	}
	init_datas_struct(&data);
	if (register_philo_input(av, &data))
	{
		ft_putstr_fd("Wrong input\n", 2);
		return (0);
	}
	if (start_vandevilling(&data))
	{
		ft_putstr_fd("Error\n", 2);
		return (0);
	}
	return (0);
}
