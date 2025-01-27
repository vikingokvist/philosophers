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
	t_table		*table;

	if (argc != 6)
		return (1);
	table = malloc(sizeof(t_table));
	if (!table)
		return (1);
	if (init_struct(table, argv))
		return (free_table(table), 1);
	if (set_forks(table))
		return (free_table(table), 1);
	if (create_threads(table))
		return (free_table(table), 1);
	return (free_table(table), 0);
}
