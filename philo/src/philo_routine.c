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
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = philo->start_time;
	pthread_mutex_unlock(philo->meal_lock);
	wait_for_threads(philo->start_time);
	if (philo->id % 2 != 0)
		precise_think(philo, 1);
	while (simulation_continues(philo))
	{
		eat_and_sleep(philo);
		precise_think(philo, 0);
	}
	return (NULL);
}

void	eat_and_sleep(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	status_msg(philo, &philo->id, MSG_FORK);
	pthread_mutex_lock(philo->r_fork);
	status_msg(philo, &philo->id, MSG_FORK);
	status_msg(philo, &philo->id, MSG_EAT);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat);
	if (simulation_continues(philo))
	{
		pthread_mutex_lock(philo->meal_lock);
		philo->meals_had += 1;
		pthread_mutex_unlock(philo->meal_lock);
	}
	status_msg(philo, &philo->id, MSG_SLEEP);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	ft_usleep(philo->time_to_sleep);
}

void	precise_think(t_philo *philo, int mod)
{
	long	think;

	pthread_mutex_lock(philo->meal_lock);
	think = (philo->time_to_die - (get_time() - philo->last_meal) - philo->time_to_eat) / 2;
	pthread_mutex_unlock(philo->meal_lock);
	if (think < 0)
		think = 0;
	if (think == 0 && mod == 1)
		think = 1;
	if (think > 600)
		think = 200;
	if (mod == 0)
		status_msg(philo, &philo->id, MSG_THINK);
	ft_usleep(think);
}

void	status_msg(t_philo *philo, size_t *id, char *string)
{
	size_t	time;

	pthread_mutex_lock(philo->write_lock);
	time = get_time() - philo->start_time;
	printf("%zu %zu %s", time, *id, string);
	pthread_mutex_unlock(philo->write_lock);
}
