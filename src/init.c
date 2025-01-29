/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:37:31 by ctommasi          #+#    #+#             */
/*   Updated: 2025/01/27 11:37:32 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_table(t_table *table, char **argv, pthread_mutex_t *forks)
{
	table->philosophers_count = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	table->meals_had_by_philos = 0;
	table->meals_to_have = -1;
	if (argv[5])
		table->meals_to_have = ft_atoi(argv[5]);
	table->someone_died = 0;
	table->forks = forks;
}

int	init_forks(t_table *table)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&table->write_lock, NULL) != 0)
	{
		printf(ERR_MUTEX_INIT);
		return (1);
	}
	if (pthread_mutex_init(&table->meal_lock, NULL) != 0)
	{
		printf(ERR_MUTEX_INIT);
		return (1);
	}
	while (i < table->philosophers_count)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
		{
			printf(ERR_MUTEX_INIT);
			return (1);
		}
		i++;
	}
	return (0);
}

void	init_philos(t_table *table, t_philo *philos)
{
	int	i;
	size_t	start_time;

	i = 0;
	start_time = get_time();
	while (i < table->philosophers_count)
	{
		philos[i].thread = 0;
		philos[i].id = i;
		philos[i].meals_had = 0;
		philos[i].start_time = start_time;
		philos[i].last_meal = start_time;
		philos[i].is_eating = 0;
		philos[i].table = table;
		philos[i].write_lock = &table->write_lock;
		philos[i].meal_lock = &table->meal_lock;
		i++;
	}
}