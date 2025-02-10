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

#include "../include/philosophers_bonus.h"

void	*table_routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	sem_wait(philo->sim_sem);
	sem_post(philo->sim_sem);
	while (1)
	{
		if ((get_time() - philo->last_meal) > philo->time_to_die)
		{
			status_msg(philo, &philo->id, MSG_DEATH);
			philo->table->simulation_continues = 0;
			exit(EXIT_FAILURE);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}

int	simulation_continues(t_philo *philo)
{
	int	state;

	sem_wait(philo->sim_sem);
	state = philo->table->simulation_continues;
	sem_post(philo->sim_sem);
	return (state);
}
