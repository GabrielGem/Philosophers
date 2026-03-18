/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 11:06:33 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/03/18 17:43:57 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>

enum e_states
{
	TAKEN_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DIED
};

typedef struct s_philo	t_philo;

typedef struct s_data
{
	int				number_of_philosophers;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	int				dead;
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
	pthread_t		thread_id;
	int				id;
	long			last_meal;
	int				number_of_meals;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t *fork_right;
	pthread_mutex_t	meal_lock;
	int				state;
}	t_philo;

long	ft_atoi(char *str);
void	*routine(void *arg);
void	ft_msleep(long msec);
void	*routine_monitor(void *arg);
long	get_current_time(void);

#endif
