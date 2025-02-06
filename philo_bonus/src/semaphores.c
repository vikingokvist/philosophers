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
	sem_close(philo->table->semaphores);
	sem_close(philo->table->sim_sem);
	sem_close(philo->table->write_sem);
	sem_close(philo->table->dead_sem);
	sem_close(philo->table->meal_sem);
	unlink_semaphores();
}

void	unlink_semaphores(void)
{
	sem_unlink("/semaphores");
	sem_unlink("/sim_sem");
	sem_unlink("/write_sem");
	sem_unlink("/dead_sem");
	sem_unlink("/meal_sem");
}

