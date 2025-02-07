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

int	philo_routine(t_philo *philo)
{
	if (pthread_create(&philo->table->table_thread, NULL, &table_routine, (void *)philo) != 0)
		return (printf(ERR_THREAD_CREATE), 1);
	if (philo->table->philosophers_count == 1)
		return (one_philosopher(philo));
	if (philo->id % 2 != 0)
		ft_usleep(philo, 1);
	while (simulation_continues(philo))
	{
		eat_and_sleep(philo);
	}
	pthread_detach(philo->table->table_thread);
	return (0);
}

void	eat_and_sleep(t_philo *philo)
{
	sem_wait(philo->table->forks);
	status_msg(philo, &philo->id, MSG_FORK);
	sem_wait(philo->table->forks);
	status_msg(philo, &philo->id, MSG_FORK);
	sem_wait(philo->meal_sem);
	status_msg(philo, &philo->id, MSG_EAT);
	philo->last_meal = get_time();
	sem_post(philo->meal_sem);
	ft_usleep(philo, philo->time_to_eat);
	if (simulation_continues(philo))
	{
		sem_wait(philo->meal_sem);
		philo->meals_had += 1;
		sem_post(philo->meal_sem);
	}
	status_msg(philo, &philo->id, MSG_SLEEP);
	sem_post(philo->table->forks);
	sem_post(philo->table->forks);
	ft_usleep(philo, philo->time_to_sleep);
	status_msg(philo, &philo->id, MSG_THINK);
}

void	status_msg(t_philo *philo, size_t *id, char *string)
{
	size_t	time;

	if (!simulation_continues(philo))
		return ;
	sem_wait(philo->write_sem);
	time = get_time() - philo->start_time;
	printf("%zu %zu %s", time, *id, string);
	sem_post(philo->write_sem);
}

int	one_philosopher(t_philo *philo)
{
	sem_wait(philo->table->forks);
	status_msg(philo, &philo->id, MSG_FORK);
	ft_usleep(philo, philo->time_to_die);
	status_msg(philo, &philo->id, MSG_DEATH);
	sem_post(philo->table->forks);
	return (0);
}
