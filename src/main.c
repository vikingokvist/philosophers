/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:20:50 by ctommasi          #+#    #+#             */
/*   Updated: 2025/01/24 13:21:29 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_table		table;
	t_philo		philos[PHILOS_MAX];
	pthread_mutex_t	forks[PHILOS_MAX];

	if (argc >= 5 && argc <= 6)
		return (write(1, "Wrong amount of arguments\n", 27), 1);
	if (check_valid_values(argc, argv))
		return (write(1, "Wrong values\n", 14), 1);
	init_table(&table, argv, forks);
	init_forks(&table);
	init_philos(&table, philos);
	create_threads(philos);
	free_table(philos);
	return (0);
}
