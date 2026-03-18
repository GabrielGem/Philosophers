/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 11:05:39 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/03/17 19:27:06 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void set_the_table(t_data *table, char **argv);
static t_philo	*list_the_guests(int amount);

int	main(int argc, char **argv)
{
	t_data	table;

	if (argc < 5 || argc > 6)
		return (0); // message showing how it works
	set_the_table(&table, (argv + 1));
	return (0);
}

static void set_the_table(t_data *table, char **argv)
{
	int	i;
	struct timeval	start_tv;

	//TODO validation for negative arguments
	table->number_of_philosophers = ft_atoi(argv[0]);
	table->time_to_die = ft_atoi(argv[1]);
	table->time_to_eat = ft_atoi(argv[2]);
	table->time_to_sleep = ft_atoi(argv[3]);
	if (argv[4])
		table->number_of_times_each_philosopher_must_eat = ft_atoi(argv[4]);
	table->dead = 0;
	table->philos = list_the_guests(table->number_of_philosophers);
	table->forks = calloc(table->number_of_philosophers, sizeof(pthread_mutex_t));
	i = -1;
	while (++i < table->number_of_philosophers)
		pthread_mutex_init(&table->forks[i], NULL);
	pthread_mutex_init(&table->log_lock, NULL);
	gettimeofday(&start_tv, NULL);
	table.start_tv = (start_tv.tv_sec * 1000) + (start_tv.tv_usec / 1000);
}

static t_philo	*list_the_guests(int amount)
{
	t_philo	*list;
	t_philo *guest;
	int	i;

	list = calloc(amount, sizeof(t_philo));
	i = 0;
	while (i < amount)
	{
		guest = calloc(1, sizeof(t_philo)); // pthread id?
		//guest->thread_id = malloc(sizeof(pthread_t));
		pthread_mutex_init(&meal_lock, NULL);
		guest->id = i + 1;
		list[i] = *guest;
		i++;
	}
	return (list);
}
