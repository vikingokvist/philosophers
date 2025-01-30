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
	t_table			table;
	t_philo			philos[PHILOS_MAX];
	pthread_mutex_t	forks[PHILOS_MAX];

	if (!(argc >= 5 && argc <= 6))
		return (printf(ERR_ARGS, ERR_ARGS2), 1);
	if (check_valid_values(argv))
		return (1);
	if (init_table(&table, forks, argv))
		return (1);
	init_philos(&table, philos, argv);
	if (create_threads(philos))
		return (1);
	free_table(philos);
	return (0);
}

