/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:07:24 by ctommasi          #+#    #+#             */
/*   Updated: 2025/01/27 16:07:25 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	status_msg(t_philo **philo, int *id, char *string, int time_to_sleep)
{
	size_t time;
	
	time = get_time() - (*philo)->start_time;
	printf("%zu %d %s\n", time, *id, string);
	if (time_to_sleep != 0)
		usleep(time_to_sleep * 1000);
}

void	ph_eat(t_philo *philo, int *l_fork, int *r_fork)
{
	if (*l_fork < *r_fork)
	{
		pthread_mutex_lock(&philo->table->forks[*l_fork]);
		status_msg(&philo, &philo->id, MSG_FORK, 0);
		pthread_mutex_lock(&philo->table->forks[*r_fork]);
	}
	else
	{
		pthread_mutex_lock(&philo->table->forks[*r_fork]);
		status_msg(&philo, &philo->id, MSG_FORK, 0);
		pthread_mutex_lock(&philo->table->forks[*l_fork]);
	}
	status_msg(&philo, &philo->id, MSG_FORK, 0);
	status_msg(&philo, &philo->id, MSG_EAT, philo->table->time_to_eat);
	philo[philo->id].last_meal = get_time() - philo->start_time;

	pthread_mutex_unlock(&philo->table->forks[*l_fork]);
	pthread_mutex_unlock(&philo->table->forks[*r_fork]);
}

void	*do_routine(void *param)
{
	t_philo *philo;
	int	l_fork;
	int	r_fork;
	int	temp;

	philo = (t_philo *)param;
	l_fork = philo->id;
	r_fork = (philo->id + 1) % philo->table->philosophers_count;
	if (philo->id % 2 != 0)
	{
		usleep(philo->table->time_to_eat * 500);
		temp = r_fork;
		r_fork = l_fork;
		l_fork = temp;
	}
	while (!philo->table->someone_died)
	{
		ph_eat(philo, &l_fork, &r_fork);
		status_msg(&philo, &philo->id, MSG_SLEEP, philo->table->time_to_sleep);
		status_msg(&philo, &philo->id, MSG_THINK, 0);
	}
	return (NULL);
}
