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

#include "../include/philosophers.h"

int	check_valid_values(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (printf(ERR_ARGS_VALID), 1);
			j++;
		}
		i++;
	}
	i = 1;
	while (argv[i])
	{
		if (i == 1 && (ft_atol(argv[i]) > PHILOS_MAX || ft_atol(argv[i]) <= 0))
			return (printf(ERR_ARGS_PHILO_MAX), 1);
		else if (ft_atol(argv[i]) <= 0 || ft_atol(argv[i]) >= UINT_MAX)
			return (printf(ERR_ARGS_VALID), 1);
		i++;
	}
	return (0);
}

int	init_table(t_table *table, pthread_mutex_t *forks, char **argv)
{
	size_t	i;

	table->philosophers_count = ft_atol(argv[1]);
	table->forks = forks;
	table->simulation_continues = 1;
	i = 0;
	while (i < table->philosophers_count)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
			return (printf(ERR_MUTEX_INIT), 1);
		i++;
	}
	if (pthread_mutex_init(&table->dead_lock, NULL) != 0)
		return (printf(ERR_MUTEX_INIT), 1);
	if (pthread_mutex_init(&table->write_lock, NULL) != 0)
		return (printf(ERR_MUTEX_INIT), 1);
	if (pthread_mutex_init(&table->meal_lock, NULL) != 0)
		return (printf(ERR_MUTEX_INIT), 1);
	return (0);
}

void	init_philos(t_table *table, t_philo *philos, char **argv,
		size_t start_time)
{
	size_t		i;

	i = 0;
	while (i < table->philosophers_count)
	{
		philos[i].id = i;
		philos[i].time_to_die = ft_atol(argv[2]);
		philos[i].time_to_eat = ft_atol(argv[3]);
		philos[i].time_to_sleep = ft_atol(argv[4]);
		philos[i].meals_to_have = 0;
		if (argv[5])
			philos[i].meals_to_have = ft_atol(argv[5]);
		philos[i].meals_had = 0;
		philos[i].start_time = start_time;
		philos[i].table = table;
		philos[i].l_fork = &table->forks[i];
		philos[i].r_fork = &table->forks[(i + 1) % table->philosophers_count];
		if (philos[i].id % 2 != 0)
		{
			philos[i].l_fork = &table->forks[(i + 1) % table->philosophers_count];
			philos[i].r_fork = &table->forks[i];
		}
		philos[i].write_lock = &table->write_lock;
		philos[i].dead_lock = &table->dead_lock;
		philos[i].meal_lock = &table->meal_lock;
		philos[i].sim_lock = &table->sim_lock;
		i++;
	}
}
