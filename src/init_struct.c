/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:37:31 by ctommasi          #+#    #+#             */
/*   Updated: 2025/01/27 11:37:32 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_struct(t_table *table, char **argv)
{
	table->number_of_philosophers = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	table->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	table->timestamp_in_ms = 0;
	table->thread = malloc(sizeof(pthread_t) * table->number_of_philosophers);
	if (!table->thread)
		return (1);
	table->fork = malloc(sizeof(pthread_mutex_t) * table->number_of_philosophers + 1);
	if (!table->fork)
		return (1);
	if (init_philos(table))
		return (1);
	return (0);
}

int	init_philos(t_table *table)
{
	int	i;

	i = 0;
	table->philosophers = malloc(sizeof(t_philo *) * table->number_of_philosophers + 1);
	if (!table->philosophers)
		return (1);
	i = 0;
	while (i < table->number_of_philosophers)
	{
		table->philosophers[i] = malloc(sizeof(t_philo));
		if (!table->philosophers[i])
			return (1);
		table->philosophers[i]->id = i;
		table->philosophers[i]->times_eaten = 0;
		i++;
	}
	return (0);
}