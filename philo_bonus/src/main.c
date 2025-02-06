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

#include "../include/philosophers_bonus.h"

int	main(int argc, char **argv)
{
	t_table			table;
	t_philo			philos[PHILOS_MAX];
	sem_t			forks[PHILOS_MAX];

	if (!(argc >= 5 && argc <= 6))
		return (printf(ERR_ARGS, ERR_ARGS2), 1);
	if (check_valid_values(argv))
		return (1);
	if (init_table(&table, forks, argv))
		return (free_semaphores(philos), 1);
	if (start_simulation(philos))
		return (free_semaphores(philos), printf(ERR_FORKS), 1);
	free_semaphores(philos);
	return (0);
}
