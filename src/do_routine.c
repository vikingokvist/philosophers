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

void	ph_think(t_philo *philo)
{
	printf("%d - %s - is thinking -      🤔\n", get_time(), philosopher_name(philo->id));
}

void	ph_sleep(t_philo *philo)
{
	printf("%d - %s - is sleeping -      💤\n", get_time(), philosopher_name(philo->id));
	usleep(philo->table->time_to_sleep * 1000);
}

void	ph_eat(t_philo *philo, int *l_fork, int *r_fork)
{
	if (*l_fork < *r_fork)
	{
		pthread_mutex_lock(&philo->table->forks[*l_fork]);
		printf("%d - %s - has taken a fork - 🍴\n", get_time(), philosopher_name(philo->id));
		pthread_mutex_lock(&philo->table->forks[*r_fork]);
		printf("%d - %s - has taken a fork - 🍴\n", get_time(), philosopher_name(philo->id));
	}
	else
	{
		pthread_mutex_lock(&philo->table->forks[*r_fork]);
		printf("%d - %s - has taken a fork - 🍴\n", get_time(), philosopher_name(philo->id));
		pthread_mutex_lock(&philo->table->forks[*l_fork]);
		printf("%d - %s - has taken a fork - 🍴\n", get_time(), philosopher_name(philo->id));
	}
	philo[philo->id].is_eating = 1;
	philo[philo->id].meals_had++;
	philo[philo->id].last_meal = get_time();
	usleep(philo->table->time_to_eat * 1000);
	printf("%d - %s - is eating -        🥘\n", get_time(), philosopher_name(philo->id));
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
