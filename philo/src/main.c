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

#include "../include/philosophers.h"

int	main(int argc, char **argv)
{
	size_t			start_time;
	t_table			table;
	t_philo			philos[PHILOS_MAX];
	pthread_mutex_t	forks[PHILOS_MAX];

	if (!(argc >= 5 && argc <= 6))
		return (printf(ERR_ARGS, ERR_ARGS2), 1);
	if (check_valid_values(argv))
		return (1);
	if (init_table(&table, forks, argv))
		return (free_table(philos), 1);
	start_time = get_time();
	init_philos(&table, philos, argv, start_time);
	if (create_threads(philos))
		return (free_table(philos), 1);
	free_table(philos);
	return (0);
}
