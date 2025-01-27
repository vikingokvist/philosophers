/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_forks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:17:43 by ctommasi          #+#    #+#             */
/*   Updated: 2025/01/27 16:17:44 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	set_forks(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->number_of_philosophers)
	{
		table->fork[i] = malloc(sizeof(pthread_mutex_t));
		if (!table->fork[i])
			return (1);
		if (pthread_mutex_init(table->fork[i], NULL) != 0)
			return (1);
		i++;
	}
	table->fork[i] = NULL;
	return (0);
}
