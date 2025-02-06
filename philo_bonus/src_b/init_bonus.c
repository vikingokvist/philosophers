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

#include "../include_b/philosophers_bonus.h"

void	init_philos(t_table *table, t_philo *philo, char **argv)
{
	size_t		i;
	size_t		start_time;

	i = 0;
	table->philosophers_count = ft_atol(argv[1]);
	table->simulation_continues = 1;
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
		i++;
	}
}
