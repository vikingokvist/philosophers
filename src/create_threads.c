/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:54:55 by ctommasi          #+#    #+#             */
/*   Updated: 2025/01/27 15:54:56 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	create_threads(t_philo *philos)
{
	int	i;
	int	j;

	i = 0;
	while (i < philos->table->philosophers_count)
	{
		if (pthread_create(&philos[i].thread, NULL, &do_routine, (void *)&philos[i]) != 0)
			return (printf("Failed to create thread.\n"), 1);
		usleep(1000);
		i++;
	}
	// Gestionar Muerteres
	j = 0;
	while (j < philos->table->philosophers_count)
	{
		if (pthread_join(philos[j].thread, NULL) != 0)
			return (printf("Failed joining threads.\n"), 1);
		j++;
	}
	return (0);
}
