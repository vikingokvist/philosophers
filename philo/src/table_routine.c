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

#include "../include/philosophers.h"

void	*table_routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	wait_for_threads(philo->start_time);
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
		pthread_mutex_lock(philo->meal_lock);
		if (anyone_died(&philo[i]))
		{
			pthread_mutex_unlock(philo[i].meal_lock);
			return (1);
		}
		if (philo[i].meals_to_have > 0 && philo[i].meals_had
			< philo[i].meals_to_have)
			all_ate = 0;
		pthread_mutex_unlock(philo->meal_lock);
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
	if ((get_time() - philo->last_meal) > philo->time_to_die)
	{
		status_msg(philo, &philo->id, MSG_DEATH);
		stop_simulation(philo);
		return (1);
	}
	return (0);
}

void	stop_simulation(t_philo *philo)
{
	pthread_mutex_lock(philo->sim_lock);
	philo->table->simulation_continues = 0;
	pthread_mutex_unlock(philo->sim_lock);
}

int	simulation_continues(t_philo *philo)
{
	int	state;

	pthread_mutex_lock(philo->sim_lock);
	state = philo->table->simulation_continues;
	pthread_mutex_unlock(philo->sim_lock);
	return (state);
}
