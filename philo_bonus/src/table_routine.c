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
		if (dead_or_finished_eating(philo))
			return (NULL);
	}
	return (NULL);
}

int	dead_or_finished_eating(t_philo *philo)
{
	size_t	i;
	int		all_ate;

	i = 0;
	all_ate = 1;
	while (i < philo->table->philosophers_count)
	{
		sem_wait(philo->dead_sem);
		if (anyone_died(&philo[i]))
		{
			sem_post(philo->dead_sem);
			return (1);
		}
		if (philo[i].meals_to_have > 0 && philo[i].meals_had
			< philo[i].meals_to_have)
			all_ate = 0;
		sem_post(philo->dead_sem);
		i++;
	}
	if (philo[0].meals_to_have > 0 && all_ate == 1)
	{
		stop_simulation(philo);
		return (1);
	}
	return (0);
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
