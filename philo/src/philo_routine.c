/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:07:24 by ctommasi          #+#    #+#             */
/*   Updated: 2025/01/27 16:07:25 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*philo_routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	pthread_mutex_lock(philo->sim_start);
	pthread_mutex_unlock(philo->sim_start);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = philo->table->start_time;
	pthread_mutex_unlock(philo->meal_lock);
	if (philo->table->philosophers_count == 1)
		return (one_philosopher(philo));
	if (philo->id % 2 != 0)
		ft_usleep(philo, 100);
	while (simulation_continues(philo))
	{
		eat_routine(philo);
		if (philo->meals_to_have > 0
			&& philo->meals_had >= philo->meals_to_have)
		{
			philo->table->finished += 1;
			return (pthread_mutex_unlock(philo->l_fork),
				pthread_mutex_unlock(philo->r_fork), NULL);
		}
		sleep_think_routine(philo);
	}
	return (NULL);
}

void	eat_routine(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	status_msg(philo, &philo->id, MSG_FORK);
	pthread_mutex_lock(philo->r_fork);
	status_msg(philo, &philo->id, MSG_FORK);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(philo->meal_lock);
	if (simulation_continues(philo))
	{
		pthread_mutex_lock(philo->meal_lock);
		philo->meals_had += 1;
		pthread_mutex_unlock(philo->meal_lock);
	}
	status_msg(philo, &philo->id, MSG_EAT);
	ft_usleep(philo, philo->time_to_eat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	sleep_think_routine(t_philo *philo)
{
	status_msg(philo, &philo->id, MSG_SLEEP);
	ft_usleep(philo, philo->time_to_sleep);
	status_msg(philo, &philo->id, MSG_THINK);
}

void	status_msg(t_philo *philo, size_t *id, char *string)
{
	size_t	time;

	pthread_mutex_lock(philo->write_lock);
	if (!simulation_continues(philo))
	{
		pthread_mutex_unlock(philo->write_lock);
		return ;
	}
	time = get_time() - philo->table->start_time;
	printf("%zu %zu %s", time, *id, string);
	pthread_mutex_unlock(philo->write_lock);
}
