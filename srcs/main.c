/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 11:05:39 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/03/21 19:14:07 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_table(t_data *table, char **argv);
static int	init_philos(t_data *table);
static void	run_simulation(t_data *table);

int	main(int argc, char **argv)
{
	t_data	table;

	if (!valid_args(argc, argv))
		return (1);
	if (!init_table(&table, (argv + 1)))
		return (1);
	run_simulation(&table);
	end_simulation(&table);
	return (0);
}

static int	init_table(t_data *table, char **argv)
{
	int	i;

	table->number_of_philosophers = ft_atol(argv[0]);
	table->time_to_die = ft_atol(argv[1]);
	table->time_to_eat = ft_atol(argv[2]);
	table->time_to_sleep = ft_atol(argv[3]);
	if (argv[4])
		table->number_of_times_each_philosopher_must_eat = ft_atol(argv[4]);
	else
		table->number_of_times_each_philosopher_must_eat = -1;
	table->dead = 0;
	table->start_sim = get_current_time();
	table->forks = calloc(table->number_of_philosophers, \
sizeof(pthread_mutex_t));
	if (!table->forks)
		return (0);
	i = -1;
	while (++i < table->number_of_philosophers)
		pthread_mutex_init(&table->forks[i], NULL);
	if (!init_philos(table))
		return (0);
	pthread_mutex_init(&table->log_lock, NULL);
	pthread_mutex_init(&table->dead_lock, NULL);
	return (1);
}

static int	init_philos(t_data *table)
{
	int		i;
	int		n;

	n = table->number_of_philosophers;
	table->philos = calloc(n, sizeof(t_philo));
	if (!table->philos)
		return (0);
	i = 0;
	while (i < n)
	{
		table->philos[i].table = table;
		table->philos[i].id = i + 1;
		table->philos[i].last_meal = get_current_time();
		table->philos[i].fork_right = &table->forks[i % n];
		table->philos[i].fork_left = &table->forks[(i + 1) % n];
		pthread_mutex_init(&table->philos[i].meal_lock, NULL);
		i++;
	}
	return (1);
}

static void	run_simulation(t_data *table)
{
	int		i;
	t_philo	*philos;

	philos = table->philos;
	i = 0;
	while (i < table->number_of_philosophers)
	{
		pthread_create(&philos[i].thread_id, NULL, routine, &philos[i]);
		i++;
	}
	pthread_create(&table->monitor, NULL, routine_monitor, table);
	i = 0;
	while (i < table->number_of_philosophers)
	{
		pthread_join(philos[i].thread_id, NULL);
		i++;
	}
	pthread_join(table->monitor, NULL);
}
