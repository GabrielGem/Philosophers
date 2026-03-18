/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 11:05:39 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/03/18 18:32:23 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void set_the_table(t_data *table, char **argv);
static t_philo	*list_the_guests(t_data *table);

int	main(int argc, char **argv)
{
	t_data	table;
	int		i;

	if (argc < 5 || argc > 6)
		return (0); // TODO message showing how it works
	set_the_table(&table, (argv + 1));
	i = -1;
	while (++i < table.number_of_philosophers)
		pthread_create(&table.philos[i].thread_id, NULL, routine, &table.philos[i]);
	pthread_create(&table.monitor, NULL, routine_monitor, &table);
	i = -1;
	while (++i < table.number_of_philosophers)
		pthread_join(table.philos[i].thread_id, NULL);
	pthread_join(table.monitor, NULL);
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
	table->philos = list_the_guests(table);
	table->forks = calloc(table->number_of_philosophers, sizeof(pthread_mutex_t));
	i = -1;
	while (++i < table->number_of_philosophers)
		pthread_mutex_init(&table->forks[i], NULL);
	pthread_mutex_init(&table->log_lock, NULL);
	table->start_sim = get_current_time();
	pthread_mutex_init(&table->dead_lock, NULL);
}

static t_philo	*list_the_guests(t_data *table)
{
	t_philo	*list;
	t_philo *guest;
	int	i;

	list = calloc(table->number_of_philosophers, sizeof(t_philo));
	i = 0;
	while (i < table->number_of_philosophers)
	{
		guest = calloc(1, sizeof(t_philo)); // pthread id?
		//guest->thread_id = malloc(sizeof(pthread_t));
		pthread_mutex_init(&guest->meal_lock, NULL);
		guest->id = i + 1;
		guest->table = table;
		list[i] = *guest;
		i++;
	}
	return (list);
}
