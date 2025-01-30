/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:56:36 by ctommasi          #+#    #+#             */
/*   Updated: 2025/01/30 12:56:37 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	all_finished_eating(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->table->philosophers_count)
	{
		if (philo[i].meals_had < philo[i].meals_to_have)
			return (0);
	}
	return (1);
}

void	*table_routine(void *param)
{
	t_philo	*philo;
	size_t	i;

	philo = (t_philo *)param;
	i = 0;
	while (1)
	{
		if (all_finished_eating(philo))
		{
			philo->table->had_all_meals = 1;
			printf(MSG_DONE);
			free_table(philo);
		}
		if ((get_time() - philo[i].last_meal) >= philo[i].time_to_die && philo[i].is_eating == 0)
		{
			philo->table->someone_died = 1;
			status_msg(philo, &i, MSG_DEATH);
			free_table(philo);
		}
		i = (i + 1) % philo->table->philosophers_count - 1;
	}
}
