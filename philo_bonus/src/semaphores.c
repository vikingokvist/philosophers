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

void	free_semaphores(t_philo *philo)
{
	if (sem_close(philo->table->semaphores) == -1)
		printf(ERR_SEM_CLOSE);
	if (sem_close(philo->table->sim_sem) == -1)
		printf(ERR_SEM_CLOSE);
	if (sem_close(philo->table->write_sem) == -1)
		printf(ERR_SEM_CLOSE);
	if (sem_close(philo->table->dead_sem) == -1)
		printf(ERR_SEM_CLOSE);
	if (sem_close(philo->table->meal_sem) == -1)
		printf(ERR_SEM_CLOSE);
	if (unlink_semaphores())
		printf(ERR_SEM_UNLINK);
}

int	unlink_semaphores(void)
{
	if (sem_unlink("/semaphores") == -1)
		return (1);
	if (sem_unlink("/sim_sem") == -1)
		return (1);
	if (sem_unlink("/write_sem") == -1)
		return (1);
	if (sem_unlink("/dead_sem") == -1)
		return (1);
	if (sem_unlink("/meal_sem") == -1)
		return (1);
	return (0);
}

int	open_semaphores(t_table *table)
{
	table->semaphores = sem_open("/semaphores", O_CREAT, 0644, table->philosophers_count);
	if (table->semaphores == SEM_FAILED)
		return (1);
	table->meal_sem = sem_open("/meal_sem", O_CREAT, 0644, 1);
	if (table->meal_sem == SEM_FAILED)
		return (1);
	table->dead_sem = sem_open("/dead_sem", O_CREAT, 0644, 1);
	if (table->dead_sem == SEM_FAILED)
		return (1);
	table->sim_sem = sem_open("/sim_sem", O_CREAT, 0644, 1);
	if (table->sim_sem == SEM_FAILED)
		return (1);
	table->write_sem = sem_open("/write_sem", O_CREAT, 0644, 1);
	if (table->write_sem == SEM_FAILED)
		return (1);
	return (0);
}
