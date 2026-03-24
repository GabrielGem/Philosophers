/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 17:29:17 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/03/24 18:19:53 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	pick_up_forks(t_philo *philo);
static int	eat(t_philo *philo);
static int	nap(t_philo *philo);
static int	think(t_philo *philo);

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->table->number_of_philosophers == 1)
	{
		log_print(philo, TAKEN_FORK);
		ft_msleep(philo->table->time_to_die);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		ft_msleep(100);
	while (1)
	{
		if (pick_up_forks(philo))
			break ;
		if (eat(philo))
			break ;
		if (nap(philo))
			break ;
		if (think(philo))
			break ;
	}
	return (NULL);
}

static int	pick_up_forks(t_philo *philo)
{
	void	*first;
	void	*second;

	if (philo->id % 2 == 0)
	{
		first = philo->fork_right;
		second = philo->fork_left;
	}
	else
	{
		first = philo->fork_left;
		second = philo->fork_right;
	}
	if (dead(philo->table))
		return (1);
	pthread_mutex_lock(first);
	log_print(philo, TAKEN_FORK);
	if (dead(philo->table))
	{
		pthread_mutex_unlock(first);
		return (1);
	}
	pthread_mutex_lock(second);
	log_print(philo, TAKEN_FORK);
	return (0);
}

static int	eat(t_philo *philo)
{
	if (dead(philo->table))
	{
		pthread_mutex_unlock(philo->fork_right);
		pthread_mutex_unlock(philo->fork_left);
		return (1);
	}
	log_print(philo, EATING);
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = get_current_time();
	philo->number_of_meals++;
	pthread_mutex_unlock(&philo->meal_lock);
	ft_msleep(philo->table->time_to_eat);
	pthread_mutex_unlock(philo->fork_right);
	pthread_mutex_unlock(philo->fork_left);
	return (0);
}

static int	nap(t_philo *philo)
{
	if (dead(philo->table))
		return (1);
	log_print(philo, SLEEPING);
	ft_msleep(philo->table->time_to_sleep);
	return (0);
}

static int	think(t_philo *philo)
{
	if (dead(philo->table))
		return (1);
	log_print(philo, THINKING);
	ft_msleep(1);
	return (0);
}
