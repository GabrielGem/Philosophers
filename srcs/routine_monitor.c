/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_monitor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 14:38:36 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/03/18 18:11:47 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine_monitor(void *arg)
{
	long	now;
	long	timestamp;
	t_data	*table;
	int		i;

	table = (t_data *)arg;
	i = 0;
	while (1)
	{
		pthread_mutex_lock(&table->philos[i].meal_lock);
		timestamp = get_current_time() - table->philos[i].last_meal;
		//printf("timestamp: %ld\n current time: %ld\n", timestamp, get_current_time());
		pthread_mutex_unlock(&table->philos[i].meal_lock);
		if (timestamp > table->time_to_die)
		{
			pthread_mutex_lock(&table->dead_lock);
			table->dead = 1;
			pthread_mutex_unlock(&table->dead_lock);
			pthread_mutex_lock(&table->log_lock);
			now = get_current_time();
			printf("%ld %d died\n", now - table->start_sim, table->philos[i].id);
			pthread_mutex_unlock(&table->log_lock);
			break ;
		}
		i++;
		i = i % table->number_of_philosophers;
		usleep(500);
	}
	return (NULL);
}
