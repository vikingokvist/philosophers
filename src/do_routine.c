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

void	print_message(int *id, char *string, int time_to_sleep)
{
	printf("[%d] (%d) %s\n", get_time(), *id, string);
	usleep(time_to_sleep * 1000);
}

void	ph_think(t_philo *philo)
{
	print_message(&philo->id, "is thinking", 0);
}

void	ph_sleep(t_philo *philo)
{
	print_message(&philo->id, "is sleeping", philo->table->time_to_sleep);
}

void	ph_eat(t_philo *philo, int *l_fork, int *r_fork)
{
	if (*l_fork < *r_fork)
	{
		pthread_mutex_lock(&philo->table->forks[*l_fork]);
		print_message(&philo->id, "has taken a fork", 0);
		pthread_mutex_lock(&philo->table->forks[*r_fork]);
		print_message(&philo->id, "has taken a fork", 0);
	}
	else
	{
		pthread_mutex_lock(&philo->table->forks[*r_fork]);
		print_message(&philo->id, "has taken a fork", 0);
		pthread_mutex_lock(&philo->table->forks[*l_fork]);
		print_message(&philo->id, "has taken a fork", 0);
	}
	philo[philo->id].is_eating = 1;
	philo[philo->id].meals_had++;
	philo[philo->id].last_meal = get_time();
	print_message(&philo->id, "is eating", philo->table->time_to_eat);
	pthread_mutex_unlock(&philo->table->forks[*l_fork]);
	pthread_mutex_unlock(&philo->table->forks[*r_fork]);
	philo[philo->id].is_eating = 0;
}

void	*do_routine(void *param)
{
	t_philo *philo;
	int	l_fork;
	int	r_fork;

	philo = (t_philo *)param;
	if (philo->id % 2 == 0)
	{
		l_fork = philo->id;
		r_fork = (philo->id + 1) % philo->table->philosophers_count;
	}
	else
	{
		l_fork = (philo->id + 1) % philo->table->philosophers_count;
		r_fork = philo->id;
	}
	while (!philo->table->someone_died)
	{

		ph_eat(philo, &l_fork, &r_fork);
		ph_sleep(philo);
		ph_think(philo);
	}
	return (NULL);
}
