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

int	create_threads(t_philo *philo)
{
	int	i;
	int	j;

	i = 0;
	while (i < philo->table->philosophers_count)
	{
		if (pthread_create(&philo[i].thread, NULL, &do_routine, (void *)&philo[i]) != 0)
			return (printf("Failed to create thread.\n"), 1);
		i++;
	}
	// Gestionar Muerteres
	j = 0;
	while (j < philo->table->philosophers_count)
	{
		if (pthread_join(philo[j].thread, NULL) != 0)
			return (printf("Failed joining threads.\n"), 1);
		j++;
	}
	return (0);
}
