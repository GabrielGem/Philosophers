/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_msleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 15:02:35 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/03/21 19:18:13 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long	get_elapsed_time_us(struct timeval start, struct timeval end);

void	ft_msleep(long msec)
{
	struct timeval	start;
	struct timeval	current;
	long			elapsed;
	long			remain;
	long			usec;

	usec = msec * 1000;
	gettimeofday(&start, NULL);
	elapsed = 0;
	while (elapsed < usec)
	{
		gettimeofday(&current, NULL);
		elapsed = get_elapsed_time_us(start, current);
		remain = usec - elapsed;
		if (remain > 1000)
			usleep(remain >> 1);
	}
}

static long	get_elapsed_time_us(struct timeval start, struct timeval end)
{
	return ((end.tv_sec - start.tv_sec) * 1000000L + \
(end.tv_usec - start.tv_usec));
}
