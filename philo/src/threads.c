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

#include "../include/philosophers.h"

int	create_threads(t_philo *philo)
{
	size_t	i;

	i = 0;
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
	pthread_mutex_destroy(philo->sim_lock);
	pthread_mutex_destroy(philo->meal_lock);
	pthread_mutex_destroy(philo->write_lock);
	i = 0;
	while (i < philo->table->philosophers_count)
	{
		pthread_mutex_destroy(&philo->table->forks[i]);
		i++;
	}
}
