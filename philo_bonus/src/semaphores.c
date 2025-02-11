/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphores_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:03:48 by ctommasi          #+#    #+#             */
/*   Updated: 2025/02/06 16:03:51 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers_bonus.h"

int	open_semaphores(t_table *table)
{
	table->forks = sem_open(SEM_FORKS, O_CREAT, 0644,
			table->philosophers_count);
	if (table->forks == SEM_FAILED)
		return (printf(ERR_SEM_OPEN), 1);
	table->meal_sem = sem_open(SEM_MEAL, O_CREAT, 0644, 1);
	if (table->meal_sem == SEM_FAILED)
		return (printf(ERR_SEM_OPEN), 1);
	table->sim_sem = sem_open(SEM_SIM, O_CREAT, 0644, 1);
	if (table->sim_sem == SEM_FAILED)
		return (printf(ERR_SEM_OPEN), 1);
	table->write_sem = sem_open(SEM_WRITE, O_CREAT, 0644, 1);
	if (table->write_sem == SEM_FAILED)
		return (printf(ERR_SEM_OPEN), 1);
	table->dead_sem = sem_open(SEM_DEAD, O_CREAT, 0644, 1);
	if (table->dead_sem == SEM_FAILED)
		return (printf(ERR_SEM_OPEN), 1);
	return (0);
}

void	free_semaphores(t_philo *philo)
{
	sem_close(philo->table->forks);
	sem_close(philo->table->sim_sem);
	sem_close(philo->table->write_sem);
	sem_close(philo->table->meal_sem);
	sem_close(philo->table->dead_sem);
	unlink_semaphores();
}

void	unlink_semaphores(void)
{
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_SIM);
	sem_unlink(SEM_WRITE);
	sem_unlink(SEM_MEAL);
	sem_unlink(SEM_DEAD);
}
