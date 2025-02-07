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
	pthread_mutex_lock(philo->dead_lock);
	pthread_mutex_unlock(philo->dead_lock);
	philo->start_time = philo->table->start_time;
	philo->last_meal = philo->table->start_time;
	if (philo->table->philosophers_count == 1)
		return (one_philosopher(philo));
	if (philo->id % 2 != 0)
		ft_usleep(philo, 100);
	while (simulation_continues(philo))
	{
		if (anyone_died(philo))
			return (NULL);
		eat_and_sleep_think(philo);
		if (philo->meals_to_have > 0
			&& philo->meals_had >= philo->meals_to_have)
			return (NULL);
	}
	return (NULL);
}

void	eat_and_sleep_think(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	status_msg(philo, &philo->id, MSG_FORK);
	pthread_mutex_lock(philo->r_fork);
	status_msg(philo, &philo->id, MSG_FORK);
	status_msg(philo, &philo->id, MSG_EAT);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo, philo->time_to_eat);
	if (simulation_continues(philo))
	{
		pthread_mutex_lock(philo->meal_lock);
		philo->meals_had += 1;
		pthread_mutex_unlock(philo->meal_lock);
	}
	status_msg(philo, &philo->id, MSG_SLEEP);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	ft_usleep(philo, philo->time_to_sleep);
	status_msg(philo, &philo->id, MSG_THINK);
}

void	status_msg(t_philo *philo, size_t *id, char *string)
{
	size_t	time;

	if (!simulation_continues(philo))
		return ;
	pthread_mutex_lock(philo->write_lock);
	time = get_time() - philo->start_time;
	printf("%zu %zu %s", time, *id, string);
	pthread_mutex_unlock(philo->write_lock);
}
