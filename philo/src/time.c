/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:35:39 by ctommasi          #+#    #+#             */
/*   Updated: 2025/01/27 11:35:41 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	wait_for_threads(size_t start_time)
{
	while (get_time() < start_time)
		continue ;
}

void	ft_usleep(t_philo *philo, size_t time_to_usleep)
{
	size_t	wake_up;

	wake_up = get_time() + time_to_usleep;
	while (get_time() < wake_up)
	{
		if (!simulation_continues(philo))
			break ;
		usleep(100);
	}
}

size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (printf(ERR_TIME), -1);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
