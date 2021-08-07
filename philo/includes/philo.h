/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 16:50:08 by gpetit            #+#    #+#             */
/*   Updated: 2021/08/07 10:47:59 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# define ERROR -1
# define SUCCESS 0
typedef struct s_philo
{
	int	nb;
	int	ttd;
	int	tte;
	int	tts;
	int	meals_flag;
	int	meals;
}	t_philo;

//UTILS
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr(char *s);
void	ft_putchar(char c);
int		ft_isdigit(int c);
long	ft_atoi(const char *str);
int		register_philo_input(char **av, t_philo *philo);

#endif
