/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:20:50 by ctommasi          #+#    #+#             */
/*   Updated: 2025/01/24 13:21:29 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_table			table;
	t_philo			philos[PHILOS_MAX];
	pthread_mutex_t	forks[PHILOS_MAX];

	if (argc != 6 || argc != 6)
		return (printf(ERR_ARGS), 1);
	check_valid_values(argc, argv);
	init_table(&table, forks, argv);
	init_philos(&table, philos, argv);
	create_threads(philos);
	free_table(philos);
	return (0);
}

void	check_valid_values(int argc, char **argv)
{
	if (ft_atol(argv[1]) > PHILOS_MAX || ft_atol(argv[1]) <= 0)
		return (printf(ERR_ARGS_VALID), exit(1));
	else if (ft_atol(argv[2]) <= 0 || ft_atol(argv[2]) >= INT_MAX)
		return (printf(ERR_ARGS_VALID), exit(1));
	else if (ft_atol(argv[3]) <= 0 || ft_atol(argv[3]) >= INT_MAX)
		return (printf(ERR_ARGS_VALID), exit(1));
	else if (ft_atol(argv[4]) <= 0 || ft_atol(argv[4]) >= INT_MAX)
		return (printf(ERR_ARGS_VALID), exit(1));
	else if (argc == 6 && (ft_atol(argv[5]) <= 0 || ft_atol(argv[5]) >= INT_MAX))
		return (printf(ERR_ARGS_VALID), exit(1));
}
