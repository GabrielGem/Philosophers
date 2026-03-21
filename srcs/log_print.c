/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 19:09:36 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/03/20 20:09:43 by gabrgarc         ###   ########.fr       */
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
	if (state == DIED)
		message = "died";
	pthread_mutex_lock(&philo->table->log_lock);
	now = get_current_time();
	printf("%ld %d %s\n", now - philo->table->start_sim, philo->id, message);
	pthread_mutex_unlock(&philo->table->log_lock);
}
