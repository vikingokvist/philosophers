/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:56:36 by ctommasi          #+#    #+#             */
/*   Updated: 2025/01/30 12:56:37 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

// int	all_finished_eating(t_philo *philo)
// {
// 	int	i;

// 	i = 0;
// 	while (i < philo->table->philosophers_count)
// 	{
// 		pthread_mutex_lock(philo->meal_lock);
// 		printf("meals had [%d] %zu\n", i, philo[i].meals_had);
// 		if (philo[i].meals_had >= philo[i].meals_to_have)
// 			philo->table->had_all_meals++;
// 		pthread_mutex_unlock(philo->meal_lock);
// 		i++;
// 	}
// 	if (philo->table->had_all_meals == philo[0].meals_to_have)
// 	{
// 		philo->table->someone_died = 1;
// 		return (1);
// 	}
// 	return (0);
// }

// int	anyone_died(t_philo *philo)
// {
// 	int	i;

// 	i = 0;
// 	while (i < philo->table->philosophers_count)
// 	{
// 		pthread_mutex_lock(philo->dead_lock);
// 		if ((get_time() - philo[i].last_meal) > philo[i].time_to_die
// 				&& philo[i].is_eating == 0)
// 		{
// 			status_msg(philo, &philo->id, MSG_DEATH);
// 			philo->table->someone_died = 1;
// 			pthread_mutex_unlock(philo->dead_lock);
// 			return (1);
// 		}
// 		pthread_mutex_unlock(philo->dead_lock);
// 		i++;
// 	}
// 	return (0);
// }

// void	*table_routine(void *param)
// {
// 	t_philo	*philo;

// 	philo = (t_philo *)param;
// 	while (1)
// 	{
// 		if (anyone_died(philo) || all_finished_eating(philo))
// 			break ;
// 	}
// 	return (NULL);
// }
