/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 18:28:09 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/03/25 13:43:29 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	valid_string(const char *str);

int	valid_args(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
	{
		printf("Usage: ./philo <number_of_philosophers> <time_to_die> ");
		printf("<time_to_eat> <time_to_sleep> ");
		printf("[number_of_times_each_philosopher_must_eat]\n");
		return (0);
	}
	i = 1;
	while (--argc)
	{
		if (!*argv[i] || ft_atol(argv[i]) < 0 || !valid_string(argv[i]))
		{
			printf("Error: all arguments must be positive integers.\n");
			return (0);
		}
		i++;
	}
	return (1);
}

static int	valid_string(const char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str) && !(*str == '+'))
			return (0);
		str++;
	}
	return (1);
}
