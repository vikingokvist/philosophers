/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:54:55 by ctommasi          #+#    #+#             */
/*   Updated: 2025/01/27 15:54:56 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers_bonus.h"

int	start_simulation(t_philo *philo)
{
	pid_t	pids[PHILOS_MAX];
	size_t	i;

	i = 0;
	while (i < philo->table->philosophers_count)
	{
		pids[i] = fork();
		if (pids[i] < 0)
			return (1);
		if (pids[i] == 0)
		{
			philo_routine(&philo[i]);
			exit(1);
		}
		i++;
	}
	kill_processes(philo, pids);
	i = 0;
	while (i < philo->table->philosophers_count)
	{
		waitpid(pids[i], NULL, 0);
		i++;
	}
	return (0);
}

void	kill_processes(t_philo *philo, pid_t *pids)
{
	pid_t	dead_pid;
	size_t	i;

	dead_pid = waitpid(-1, &philo->table->exit_status, 0);
	if (WIFEXITED(philo->table->exit_status)
		&& WEXITSTATUS(philo->table->exit_status) == 1)
	{
		i = 0;
		while (i < philo->table->philosophers_count)
		{
			if (pids[i] != dead_pid)
				kill(pids[i], SIGTERM);
			i++;
		}
	}
}
