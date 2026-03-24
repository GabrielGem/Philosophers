/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 19:09:36 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/03/24 12:12:02 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_print(t_philo *philo, t_states state)
{
	char	*message;
	long	now;

	if (state == TAKEN_FORK)
		message = "has taken a fork";
	if (state == EATING)
		message = "is eating";
	if (state == SLEEPING)
		message = "is sleeping";
	if (state == THINKING)
		message = "is thinking";
	pthread_mutex_lock(&philo->table->log_lock);
	if (dead(philo->table))
	{
		pthread_mutex_unlock(&philo->table->log_lock);
		return ;
	}
	now = get_current_time();
	printf("%ld %d %s\n", now - philo->table->start_sim, philo->id, message);
	pthread_mutex_unlock(&philo->table->log_lock);
}
