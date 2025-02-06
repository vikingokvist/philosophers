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

#include "../include/philosophers_bonus.h"

void	*philo_routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	if (philo->table->philosophers_count == 1)
		return (one_philosopher(philo));
	if (philo->id % 2 != 0)
		ft_usleep(philo, 1);
	while (simulation_continues(philo))
	{
		eat_and_sleep(philo);
		precise_think(philo);
	}
	return (NULL);
}

void	eat_and_sleep(t_philo *philo)
{
	status_msg(philo, &philo->id, MSG_FORK);
	status_msg(philo, &philo->id, MSG_FORK);
	status_msg(philo, &philo->id, MSG_EAT);
	philo->last_meal = get_time();
	ft_usleep(philo, philo->time_to_eat);
	if (simulation_continues(philo))
	{
		philo->meals_had += 1;
	}
	status_msg(philo, &philo->id, MSG_SLEEP);
	ft_usleep(philo, philo->time_to_sleep);
}

void	precise_think(t_philo *philo)
{
	ft_usleep(philo, 1);
	status_msg(philo, &philo->id, MSG_THINK);
}

void	status_msg(t_philo *philo, size_t *id, char *string)
{
	size_t	time;

	if (!simulation_continues(philo))
		return ;
	time = get_time() - philo->start_time;
	printf("%zu %zu %s", time, *id, string);
}

void	*one_philosopher(t_philo *philo)
{
	status_msg(philo, &philo->id, MSG_FORK);
	ft_usleep(philo, philo->time_to_die);
	status_msg(philo, &philo->id, MSG_DEATH);
	return (NULL);
}
