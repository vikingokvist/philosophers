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

int	anyone_died(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if ((get_time() - philo->last_meal) > philo->time_to_die)
	{
		status_msg(philo, &philo->id, MSG_DEATH);
		stop_simulation(philo);
		pthread_mutex_unlock(philo->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->dead_lock);
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

void	*one_philosopher(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	status_msg(philo, &philo->id, MSG_FORK);
	ft_usleep(philo, philo->time_to_die);
	status_msg(philo, &philo->id, MSG_DEATH);
	pthread_mutex_unlock(philo->l_fork);
	return (NULL);
}
