/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 17:33:39 by gpetit            #+#    #+#             */
/*   Updated: 2021/08/07 13:36:47 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo_struct(t_philo *philo)
{
	philo->nb = 0;
	philo->ttd = 0;
	philo->tte = 0;
	philo->tts = 0;
	philo->meals_flag = 0;
	philo->meals = 0;
}

int	main(int ac, char **av)
{
	t_philo	philo;

	if (ac != 5 && ac != 6)
	{
		ft_putstr_fd("Wrong number of arguments\n", 2);
		return (0);
	}
	init_philo_struct(&philo);
	if (register_philo_input(av, &philo))
	{
		ft_putstr_fd("Wrong input\n", 2);
		return (0);
	}
	if (start_vandevilling(&philo))
	{
		ft_putstr_fd("Error\n", 2);
		return (0);
	}
	return (0);
}
