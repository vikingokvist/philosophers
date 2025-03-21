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

void	*table_routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	while (1)
	{
		sem_wait(philo->meal_sem);
		if ((get_time() - philo->last_meal) > philo->time_to_die)
		{
			sem_wait(philo->write_sem);
			printf("%zu %zu %s", get_time() - philo->start_time,
				philo->id, MSG_DEATH);
			sem_post(philo->meal_sem);
			exit(1);
		}
		sem_post(philo->meal_sem);
		usleep(150);
	}
	return (NULL);
}

int	philo_routine(t_philo *philo)
{
	if (philo->table->philosophers_count == 1)
		return (one_philosopher(philo));
	if (pthread_create(&philo->table->table_thread, NULL,
			&table_routine, (void *)philo) != 0)
		return (printf(ERR_THREAD_CREATE), 1);
	pthread_detach(philo->table->table_thread);
	sem_wait(philo->sim_sem);
	sem_post(philo->sim_sem);
	if (philo->id % 2 != 0)
		ft_usleep(100);
	while (1)
	{
		eat_routine(philo);
		if (philo->meals_to_have > 0
			&& philo->meals_had >= philo->meals_to_have)
			exit(0);
		status_msg(philo, &philo->id, MSG_SLEEP);
		ft_usleep(philo->time_to_sleep);
		status_msg(philo, &philo->id, MSG_THINK);
		usleep(150);
	}
	return (0);
}

void	eat_routine(t_philo *philo)
{
	sem_wait(philo->table->forks);
	status_msg(philo, &philo->id, MSG_FORK);
	sem_wait(philo->table->forks);
	status_msg(philo, &philo->id, MSG_FORK);
	sem_wait(philo->meal_sem);
	philo->last_meal = get_time();
	sem_post(philo->meal_sem);
	sem_wait(philo->meal_sem);
	philo->meals_had += 1;
	sem_post(philo->meal_sem);
	status_msg(philo, &philo->id, MSG_EAT);
	ft_usleep(philo->time_to_eat);
	sem_post(philo->table->forks);
	sem_post(philo->table->forks);
}

void	status_msg(t_philo *philo, size_t *id, char *string)
{
	size_t	time;

	sem_wait(philo->write_sem);
	time = get_time() - philo->start_time;
	printf("%zu %zu %s", time, *id, string);
	sem_post(philo->write_sem);
}

int	one_philosopher(t_philo *philo)
{
	sem_wait(philo->table->forks);
	status_msg(philo, &philo->id, MSG_FORK);
	ft_usleep(philo->time_to_die);
	status_msg(philo, &philo->id, MSG_DEATH);
	sem_post(philo->table->forks);
	return (0);
}
