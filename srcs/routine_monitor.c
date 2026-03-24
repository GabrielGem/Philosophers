/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_monitor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 14:38:36 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/03/24 16:31:55 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_death(t_data *table, int i);
static int	all_satisfied(t_data *table);

void	*routine_monitor(void *arg)
{
	t_data	*table;
	int		i;

	table = (t_data *)arg;
	while (1)
	{
		i = 0;
		while (i < table->number_of_philosophers)
		{
			if (check_death(table, i))
				return (NULL);
			i++;
		}
		if (all_satisfied(table))
			return (NULL);
		usleep(500);
	}
	return (NULL);
}

static int	check_death(t_data *table, int i)
{
	long	timestamp;
	int		meals;
	long	now;

	pthread_mutex_lock(&table->philos[i].meal_lock);
	timestamp = get_current_time() - table->philos[i].last_meal;
	meals = table->philos[i].number_of_meals;
	pthread_mutex_unlock(&table->philos[i].meal_lock);
	if (timestamp > table->time_to_die
		&& (table->number_of_times_each_philosopher_must_eat == -1
			|| meals != table->number_of_times_each_philosopher_must_eat))
	{
		pthread_mutex_lock(&table->dead_lock);
		table->dead = 1;
		pthread_mutex_unlock(&table->dead_lock);
		pthread_mutex_lock(&table->log_lock);
		now = get_current_time();
		printf("%ld %d died\n", now - table->start_sim, table->philos[i].id);
		pthread_mutex_unlock(&table->log_lock);
		return (1);
	}
	return (0);
}

static int	all_satisfied(t_data *table)
{
	int	i;
	int	meals;

	if (table->number_of_times_each_philosopher_must_eat == -1)
		return (0);
	i = 0;
	while (i < table->number_of_philosophers)
	{
		pthread_mutex_lock(&table->philos[i].meal_lock);
		meals = table->philos[i].number_of_meals;
		pthread_mutex_unlock(&table->philos[i].meal_lock);
		if (meals < table->number_of_times_each_philosopher_must_eat)
			return (0);
		i++;
	}
	return (1);
}
