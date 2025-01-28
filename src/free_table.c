/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:01:07 by ctommasi          #+#    #+#             */
/*   Updated: 2025/01/27 15:01:09 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_table(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->table->philosophers_count)
	{
		pthread_mutex_destroy(&philos->table->forks[i]);
		i++;
	}
	exit(EXIT_SUCCESS);
}
