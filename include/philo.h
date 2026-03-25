/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 11:06:33 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/03/25 10:03:14 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>

typedef enum e_states
{
	TAKEN_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DIED
}	t_states;

typedef struct s_philo	t_philo;

typedef struct s_data
{
	int				number_of_philosophers;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	int				dead;
	int				start;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	log_lock;
	pthread_mutex_t	dead_lock;
	long			start_sim;
	pthread_t		monitor;
}	t_data;

typedef struct s_philo
{
	t_data			*table;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	pthread_mutex_t	meal_lock;
	pthread_t		thread_id;
	long			last_meal;
	int				id;
	int				number_of_meals;
}	t_philo;

void	*routine(void *arg);
void	*routine_monitor(void *arg);

long	get_current_time(void);
void	end_simulation(t_data *table);
void	ft_msleep(long msec);
int		dead(t_data *table);
void	log_print(t_philo *philo, t_states state);
long	ft_atol(char *str);
int		ft_isdigit(char c);
int		valid_args(int argc, char **argv);

#endif
