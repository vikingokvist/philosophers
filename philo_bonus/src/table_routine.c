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
	while (1)
	{
		sem_wait(philo->dead_sem);
		if (anyone_died(philo))
		{
			sem_post(philo->dead_sem);
			return (NULL);
		}
		if (philo->meals_to_have > 0 && philo->meals_had >= philo->meals_to_have)
		{
			stop_simulation(philo);
			sem_post(philo->dead_sem);
			return (NULL);
		}
		sem_post(philo->dead_sem);
	}
	return (NULL);
}

int	anyone_died(t_philo *philo)
{
	sem_wait(philo->dead_sem);
	if ((get_time() - philo->last_meal) > philo->time_to_die)
	{
		status_msg(philo, &philo->id, MSG_DEATH);
		stop_simulation(philo);
		sem_post(philo->dead_sem);
		return (1);
	}
	sem_post(philo->dead_sem);
	return (0);
}

void	stop_simulation(t_philo *philo)
{
	sem_wait(philo->sim_sem);
	philo->table->simulation_continues = 0;
	sem_post(philo->sim_sem);
}

int	simulation_continues(t_philo *philo)
{
	int	state;

	sem_wait(philo->sim_sem);
	state = philo->table->simulation_continues;
	sem_post(philo->sim_sem);
	return (state);
}
