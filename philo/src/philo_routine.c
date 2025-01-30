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

#include "./philosophers.h"

void	*philo_routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (1)
	{
		if (someone_died(philo))
			break ;
		ph_eat(philo);
		status_msg(philo, &philo->id, MSG_SLEEP);
		ft_usleep(philo->time_to_sleep);
		status_msg(philo, &philo->id, MSG_THINK);
	}
	return (NULL);
}

void	ph_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	status_msg(philo, &philo->id, MSG_FORK);
	pthread_mutex_lock(philo->r_fork);
	status_msg(philo, &philo->id, MSG_FORK);
	philo->is_eating = 1;
	status_msg(philo, &philo->id, MSG_EAT);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_time();
	philo->meals_had++;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat);
	philo->is_eating = 0;
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	status_msg(t_philo *philo, size_t *id, char *string)
{
	size_t	time;

	pthread_mutex_lock(philo->write_lock);
	time = get_time() - philo->start_time;
	printf("%zu %zu %s\n", time, *id, string);
	pthread_mutex_unlock(philo->write_lock);
}

int	someone_died(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (philo->table->someone_died == 1)
	{
		pthread_mutex_unlock(philo->dead_lock);
		free_table(philo);
		return (1);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}
