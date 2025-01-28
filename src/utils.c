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

int	had_all_meals(t_philo *philo)
{
	int	i;
	int	check;

	i = 1;
	check = philo[0].meals_had;
	while (i < philo->table->philosophers_count)
	{
		if (philo[i].meals_had != philo->table->meals_to_have)
			return (0);
		i++;
	}
	printf("%d - All philosophers finished their meals\n", get_time());
	return (1);
}

// int	someone_has_died(t_table *table, int *i)
// {
// 	int	index;

// 	index = table->number_of_philosophers % (*i + 1);
// 	pthread_mutex_lock(&table->forks[index]);
// 	if (get_time() - table->philosophers[index].last_meal >= table->philosophers[index].is_eating == 0)
// 	{
// 		pthread_mutex_unlock(&table->forks[index]);
// 		printf("%s: died at %d\n", philosopher_name(index), get_time());
// 		return (1);
// 	}
// 	pthread_mutex_unlock(&table->forks[index]);
// 	return (0);
// }

int	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (write(1, "Error getting time\n", 20), -1);
	return ((time.tv_usec * 1000) + (time.tv_sec / 1000));
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

char	*philosopher_name(int i)
{
	char	*philosophers[200];

	philosophers[0] = "Descartes ";
	philosophers[1] = "Aristotle ";
	philosophers[2] = "Kant      ";
	philosophers[3] = "Marx      ";
	philosophers[4] = "Plato     ";
	philosophers[5] = "Nietzsche ";
	philosophers[6] = "Engels    ";
	return (philosophers[i]);
}
