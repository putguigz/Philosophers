/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <gpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 16:50:08 by gpetit            #+#    #+#             */
/*   Updated: 2021/09/02 15:28:03 by gpetit           ###   ########.fr       */
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
# define DEATH 1
# define ALIVE 0

typedef struct s_datas
{
	int				nb;
	int				ttd;
	int				tte;
	int				tts;
	int				meals_flag;
	int				meals;
	int				death;
	int				error;
	struct timeval	time;
	struct s_philo	*philo;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	error_mutex;
}	t_datas;

typedef struct s_philo
{
	int				nb;
	int				fork;
	pthread_mutex_t	mutex;
	long			last_dinner;
	int				meal;
	struct s_datas	*data;
}	t_philo;

//AUTRES
int		start_vandevilling(t_datas *data);

//CLOCK
long	get_time_elapsed(t_datas *data);
int		my_usleep(int time, t_datas *data);

//DEATH
int		kill_philo(int current_ph, t_datas *data);
int		check_death_variable(t_datas *data);

//MULTI-THREADING
int		launch_threads(t_datas *data);
int		plato_died(int current_ph, t_datas *data);
int		monitor_everyone(t_datas *data);

//TAMAGOCHI_ACTIONS
int		tamagochi_philo(int thread_nb, t_datas *data);
int		take_forks(int current_ph, t_datas *data);
int		start_eating(int current_ph, t_datas *data);
int		drop_forks(int current_ph, t_datas *data);
int		status_printer(int current_ph, char *str, t_datas *data);

//UTILS
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr(char *s);
void	ft_putchar(char c);
int		ft_isdigit(int c);
long	ft_atoi(const char *str);
int		register_philo_input(char **av, t_datas *data);

#endif
