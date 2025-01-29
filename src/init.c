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

int	init_table(t_table *table, pthread_mutex_t *forks, char **argv)
{
	int	i;

	table->philosophers_count = ft_atol(argv[1]);
	table->meals_had_by_philos = 0;
	table->someone_died = 0;
	table->forks = forks;
	if (pthread_mutex_init(&table->dead_lock, NULL) != 0)
		return (printf(ERR_MUTEX_INIT), 1);
	if (pthread_mutex_init(&table->write_lock, NULL) != 0)
		return (printf(ERR_MUTEX_INIT), 1);
	if (pthread_mutex_init(&table->meal_lock, NULL) != 0)
		return (printf(ERR_MUTEX_INIT), 1);
	i = 0;
	while (i < table->philosophers_count)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
			return (printf(ERR_MUTEX_INIT), 1);
		i++;
	}
	return (0);
}

void	init_philos(t_table *table, t_philo *philos, char **argv)
{
	int		i;
	size_t	start_time;

	i = 0;
	start_time = get_time();
	while (i < table->philosophers_count)
	{
		philos[i].thread = 0;
		philos[i].id = i;
		philos[i].time_to_die = ft_atol(argv[2]);
		philos[i].time_to_eat = ft_atol(argv[3]);
		philos[i].time_to_sleep = ft_atol(argv[4]);
		philos[i].meals_to_have = ft_atol(argv[5]);
		philos[i].meals_had = 0;
		philos[i].start_time = start_time;
		philos[i].last_meal = start_time;
		philos[i].is_eating = 0;
		philos[i].table = table;
		philos[i].l_fork = &table->forks[i];
		philos[i].r_fork = &table->forks[(i + 1) % table->philosophers_count];
		philos[i].write_lock = &table->write_lock;
		philos[i].dead_lock = &table->dead_lock;
		philos[i].meal_lock = &table->meal_lock;
		i++;
	}
}
