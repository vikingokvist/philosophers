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

#include "../include/philosophers_bonus.h"

int	start_simulation(t_philo *philo)
{
	pid_t	pids[philo->table->philosophers_count];
	size_t	i;

	i = 0;
	while (i < philo->table->philosophers_count)
	{
		pids[i] = fork();
		if (pids[i] < 0)
			return (1);
		if (pids[i] == 0)
		{
			
			philo_routine(&philo[i]);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	i = 0;
	while (i < philo->table->philosophers_count)
	{
		waitpid(pids[i], NULL, 0);
		i++;
	}
	return (0);
}
