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

void	*do_routine(void *param)
{
	t_table	*table;

	table = (t_philo *)param;
	
	pthread_mutex_lock(&table->fork[table->philosophers->id]);

	return (NULL);
}

int	create_threads(t_table *table)
{
	int	i;
	int	j;

	i = 0;
	while (i < table->number_of_philosophers)
	{
		if (pthread_create(&table->thread[i], NULL, &do_routine, (void *)table) != 0)
			return (printf("Failed to create thread.\n"), 1);
		printf("Philosopher (%d) was born.\n", i + 1);
		i++;
	}
	j = 0;
	while (j < table->number_of_philosophers)
	{
		if (pthread_join(table->thread[j], NULL) != 0)
			return (printf("Failed joining threads.\n"), 1);
		printf("Philosopher (%d) has finished doing things.\n", j + 1);
		j++;
	}
	return (0);
}
