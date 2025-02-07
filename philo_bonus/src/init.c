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

#include "../include/philosophers_bonus.h"

int	init_table(t_table *table, char **argv)
{
	table->philosophers_count = ft_atol(argv[1]);
	table->simulation_continues = 1;
	if (unlink_semaphores())
		return (printf(ERR_SEM_UNLINK), 1);
	if (open_semaphores(table))
		return (printf(ERR_SEM_OPEN), 1);
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
		philo[i].sim_sem = table->sim_sem;
		philo[i].dead_sem = table->dead_sem;
		philo[i].meal_sem = table->meal_sem;
		philo[i].write_sem = table->write_sem;
		i++;
	}
}
