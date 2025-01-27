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

void	free_table(t_table *table)
{
	int	i;

	if (table->thread)
		free(table->thread);
	if (table->fork)
	{
		i = 0;
		while (i < table->number_of_philosophers)
		{
			if (table->fork[i])
			{
				pthread_mutex_destroy(table->fork[i]);
				free(table->fork[i]);
			}
			i++;
		}
		free(table->fork);
	}
	if (table->philosophers)
	{
		i = 0;
		while (i < table->number_of_philosophers)
		{
			if (table->philosophers[i])
				free(table->philosophers[i]);
			i++;
		}
		free(table->philosophers);
	}
	free(table);
	exit(EXIT_SUCCESS);
}
