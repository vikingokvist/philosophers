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
			return (1);
		i++;
	}
	if (pthread_mutex_init(&table->write_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&table->meal_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&table->sim_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&table->sleep_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&table->dead_lock, NULL) != 0)
		return (1);
	return (0);
}

void	init_philos(t_table *table, t_philo *philo, char **argv)
{
	size_t		i;
	size_t		start_time;

	i = 0;
	start_time = get_time();
	while (i < table->philosophers_count)
	{
		philo[i].id = i;
		philo[i].time_to_die = ft_atol(argv[2]);
		philo[i].time_to_eat = ft_atol(argv[3]);
		philo[i].time_to_sleep = ft_atol(argv[4]);
		philo[i].meals_to_have = 0;
		if (argv[5])
			philo[i].meals_to_have = ft_atol(argv[5]);
		philo[i].meals_had = 0;
		philo[i].start_time = start_time;
		philo[i].last_meal = start_time;
		philo[i].table = table;
		set_forks(philo, table, i);
		philo[i].write_lock = &table->write_lock;
		philo[i].meal_lock = &table->meal_lock;
		philo[i].sim_lock = &table->sim_lock;
		philo[i].sleep_lock = &table->sleep_lock;
		philo[i].dead_lock = &table->dead_lock;
		i++;
	}
}

void	set_forks(t_philo *philo, t_table *table, int i)
{
	if (philo[i].id % 2 == 0)
	{
		philo[i].l_fork = &table->forks[i];
		philo[i].r_fork = &table->forks[(i + 1)
			% philo->table->philosophers_count];
	}
	else if (philo[i].id % 2 != 0)
	{
		philo[i].l_fork = &table->forks[(i + 1)
			% philo->table->philosophers_count];
		philo[i].r_fork = &table->forks[i];
	}
}
