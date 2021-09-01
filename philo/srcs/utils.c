/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <gpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 10:22:08 by gpetit            #+#    #+#             */
/*   Updated: 2021/09/01 15:05:35 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		ft_putchar(s[i]);
		i++;
	}
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}

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
