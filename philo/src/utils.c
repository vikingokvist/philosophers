/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:35:39 by ctommasi          #+#    #+#             */
/*   Updated: 2025/01/27 11:35:41 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	ft_usleep(size_t time_to_usleep)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < time_to_usleep)
		usleep(500);
}

size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (printf(ERR_TIME), -1);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

long	ft_atol(const char *str)
{
	long	res;
	int		minus;
	int		i;

	i = 0;
	res = 0;
	minus = 1;
	while (str[i] == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		minus *= -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + *str - '0';
		str++;
	}
	return (res * minus);
}

void	free_table(t_philo *philo)
{
	size_t	i;

	i = 0;
	pthread_mutex_destroy(philo->dead_lock);
	pthread_mutex_destroy(philo->meal_lock);
	pthread_mutex_destroy(philo->write_lock);
	while (i < philo->table->philosophers_count)
	{
		pthread_mutex_destroy(&philo->table->forks[i]);
		i++;
	}
	exit(0);
}
