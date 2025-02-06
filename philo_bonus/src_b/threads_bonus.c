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

#include "../include_b/philosophers_bonus.h"

int	create_threads(t_philo *philo)
{
	size_t	i;

	i = 0;
	sem_init(&philo->table->semaphore, 0, 1);
	while (i < philo->table->philosophers_count)
	{
		if (pthread_create(&philo[i].thread, NULL,
				&philo_routine, (void *)&philo[i]) != 0)
		{
			printf(ERR_THREAD_CREATE);
			return (1);
		}
		i++;
	}
	if (pthread_create(&philo->table->table_thread, NULL,
			&table_routine, (void *)philo) != 0)
	{
		printf(ERR_THREAD_CREATE);
		return (1);
	}
	return (0);
}

void	join_and_destroy_threads(t_philo *philo)
{
	size_t	i;

	i = 0;
	while (i < philo->table->philosophers_count)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
			printf(ERR_THREAD_JOIN);
		i++;
	}
	if (pthread_join(philo->table->table_thread, NULL) != 0)
	{
		printf(ERR_THREAD_JOIN);
	}
	sem_destroy(&philo->table->semaphore);
}
