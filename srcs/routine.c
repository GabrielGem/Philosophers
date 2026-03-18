/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 17:29:17 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/03/18 17:52:50 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	pick_up_forks(t_philo *philo);
static void	eat(t_philo *philo);
static void	nap(t_philo *philo);
static void	think(t_philo *philo);
long	get_current_time(void);

void	*routine(void *arg)
{
	t_philo	*philo;
	int		catch;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_msleep(1);
	while (1)
	{
		// TODO fix: deadlock all philo take left fork
		pthread_mutex_lock(&philo->table->dead_lock);
		if (philo->table->dead)
			break ;
		pthread_mutex_unlock(&philo->table->dead_lock);

		catch = pick_up_forks(philo);
		if (catch) // check if he pickup up fork for eating
			eat(philo);
		nap(philo);
		think(philo);
	}
	return (NULL);
}

static int	pick_up_forks(t_philo *philo)
{
	long	now;
	long	timestamp;

	// If you fail to pick up one of the forks, it returns 0.	
	pthread_mutex_lock(&philo->table->dead_lock);
	if (philo->table->dead)
		return (0);
	pthread_mutex_unlock(&philo->table->dead_lock);

	if (pthread_mutex_lock(&philo->table->forks[philo->id % philo->table->number_of_philosophers]) != 0)
		return (0);
	pthread_mutex_lock(&philo->table->log_lock);
	now = get_current_time();
	timestamp = now - philo->table->start_sim;
	printf("%ld %d has taken a fork\n", timestamp, philo->id);
	pthread_mutex_unlock(&philo->table->log_lock);

	pthread_mutex_lock(&philo->table->dead_lock);
	if (philo->table->dead)
		return (0);
	pthread_mutex_unlock(&philo->table->dead_lock);

	// If you manage to grab the left one but not the right one, release the right one.
	if (pthread_mutex_lock(&philo->table->forks[(philo->id + 1) % philo->table->number_of_philosophers]) != 0)
	{
		pthread_mutex_unlock(&philo->table->forks[philo->id % philo->table->number_of_philosophers]);
		return (0);
	}
	pthread_mutex_lock(&philo->table->log_lock);
	now = get_current_time();
	timestamp = now - philo->table->start_sim;
	printf("%ld %d has taken a fork\n", timestamp, philo->id);
	pthread_mutex_unlock(&philo->table->log_lock);
	return (1);
}

static void	eat(t_philo *philo)
{
	long	now;
	long	timestamp;

	pthread_mutex_lock(&philo->table->dead_lock);
	if (philo->table->dead)
		return ;
	pthread_mutex_unlock(&philo->table->dead_lock);

	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(&philo->meal_lock);

	pthread_mutex_lock(&philo->table->log_lock);
	now = get_current_time();
	timestamp = now - philo->table->start_sim;
	printf("%ld %d is eating\n", timestamp, philo->id);
	pthread_mutex_unlock(&philo->table->log_lock);

	ft_msleep(philo->table->time_to_eat);

	pthread_mutex_unlock(&philo->table->forks[philo->id % philo->table->number_of_philosophers]);
	pthread_mutex_unlock(&philo->table->forks[(philo->id + 1) % philo->table->number_of_philosophers]);
}

static void	nap(t_philo *philo)
{
	long	now;
	long	timestamp;

	pthread_mutex_lock(&philo->table->dead_lock);
	if (philo->table->dead)
		return ;
	pthread_mutex_unlock(&philo->table->dead_lock);

	pthread_mutex_lock(&philo->table->log_lock);
	now = get_current_time();
	timestamp = now - philo->table->start_sim;
	printf("%ld %d is sleeping\n", timestamp, philo->id);
	pthread_mutex_unlock(&philo->table->log_lock);
	ft_msleep(philo->table->time_to_sleep);
}

static void	think(t_philo *philo)
{
	long	now;
	long	timestamp;

	pthread_mutex_lock(&philo->table->dead_lock);
	if (philo->table->dead)
		return ;
	pthread_mutex_unlock(&philo->table->dead_lock);
	// How much time should you spend thinking?
	pthread_mutex_lock(&philo->table->log_lock);
	now = get_current_time();
	timestamp = now - philo->table->start_sim;
	printf("%ld %d is thinking\n", timestamp, philo->id);
	pthread_mutex_unlock(&philo->table->log_lock);
	ft_msleep(1);
}
