/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <gpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 16:50:08 by gpetit            #+#    #+#             */
/*   Updated: 2021/08/19 11:59:41 by gpetit           ###   ########.fr       */
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

# define INT_MAX 2147483647
# define ERROR -1
# define SUCCESS 0

typedef struct s_datas
{
	int				nb;
	int				ttd;
	int				tte;
	int				tts;
	int				meals_flag;
	int				meals;
	struct timeval	time;
	struct s_philo	*philo;
	pthread_mutex_t	mutex;
}	t_datas;

typedef struct s_philo
{
	int				nb;
	int				fork;
	pthread_mutex_t	mutex;
}	t_philo;

//AUTRES
int		start_vandevilling(t_datas *data);

//CLOCK
long	get_time_elapsed(t_datas *data);

//MULTI-THREADING
int		launch_threads(t_datas *data);

//TAMAGOCHI_ACTIONS
int		tamagochi_philo(int thread_nb, t_datas *data);

//UTILS
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr(char *s);
void	ft_putchar(char c);
int		ft_isdigit(int c);
long	ft_atoi(const char *str);
int		register_philo_input(char **av, t_datas *data);

#endif
