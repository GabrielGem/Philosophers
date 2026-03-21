/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 19:07:58 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/03/20 19:20:16 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	dead(t_data *table)
{
	pthread_mutex_lock(&table->dead_lock);
	if (table->dead)
	{
		pthread_mutex_unlock(&table->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&table->dead_lock);
	return (0);
}
