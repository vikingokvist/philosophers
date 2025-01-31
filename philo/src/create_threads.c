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
	size_t	j;

	i = 0;
	while (i < philo->table->philosophers_count)
	{
		if (pthread_create(&philo[i].thread, NULL,
				&philo_routine, (void *)&philo[i]) != 0)
			return (printf(ERR_THREAD_CREATE), 1);
		i++;
	}
	j = 0;
	while (j < philo->table->philosophers_count)
	{
		if (pthread_join(philo[j].thread, NULL) != 0)
			return (printf(ERR_THREAD_JOIN), 1);
		j++;
	}
	return (0);
}
