/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 11:06:33 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/03/17 19:23:44 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>

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
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	int				dead;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	log_lock;
	struct timeval	start_tv;
}	t_data;

typedef struct s_philo
{
	t_data			*table;
	pthread_t		thread_id;
	int				id;
	int				last_meal;
	int				number_of_meals;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t *fork_right;
	pthread_mutex_t	meal_lock;
	int				state;
}	t_philo;


int	ft_atoi(char *str);

#endif
