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

#include "philosophers.h"

int	someone_has_died(t_philo *philo, int *id)
{
	if (philo[*id].last_meal >= philo->table->time_to_die)
	{
		status_msg(&philo, id, MSG_DEATH, 0);
		free_table(philo);
		return (1);
	}
	return (0);
}

size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (printf(ERR_TIME), -1);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

long	ft_atoi(const char *str)
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

int	check_valid_values(int argc, char **argv)
{
	if (ft_atoi(argv[1]) > PHILOS_MAX || ft_atoi(argv[1]) <= 0)
		return (1);
	if (ft_atoi(argv[2]) <= 0)
		return (1);
	if (ft_atoi(argv[3]) <= 0)
		return (1);
	if (ft_atoi(argv[4]) <= 0)
		return (1);
	if (argc == 6 && ft_atoi(argv[5]) <= 0)
		return (1);
	return (0);
}

