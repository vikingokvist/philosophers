/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:42:27 by ctommasi          #+#    #+#             */
/*   Updated: 2025/02/04 16:42:28 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers_bonus.h"

void	ft_usleep(size_t time_to_usleep)
{
	size_t	wake_up;

	wake_up = get_time() + time_to_usleep;
	while (get_time() < wake_up)
	{
		usleep(100);
	}
}

size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (printf(ERR_TIME), 0);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	check_valid_values(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (printf(ERR_ARGS_VALID), 1);
			j++;
		}
		i++;
	}
	i = 1;
	while (argv[i])
	{
		if (i == 1 && (ft_atol(argv[i]) > PHILOS_MAX || ft_atol(argv[i]) <= 0))
			return (printf(ERR_ARGS_PHILO_MAX), 1);
		else if (ft_atol(argv[i]) <= 0 || ft_atol(argv[i]) >= UINT_MAX)
			return (printf(ERR_ARGS_VALID), 1);
		i++;
	}
	return (0);
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
