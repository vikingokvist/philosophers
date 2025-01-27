/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:19:55 by ctommasi          #+#    #+#             */
/*   Updated: 2025/01/24 13:19:56 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSHOPHERS_H
# define PHILOSHOPHERS_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>

typedef struct s_philo
{
	int	id;
	int	times_eaten;
}	t_philo;

typedef struct s_table
{
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	timestamp_in_ms;
	int	number_of_times_each_philosopher_must_eat;
	int	someone_died;
	pthread_t	*thread;
	pthread_mutex_t **fork;
	t_philo		**philosophers;
}	t_table;

//-----------------------------------------------SRC
int		main(int argc, char **argv);
int		init_struct(t_table *table, char **argv);
int		create_threads(t_table *table);
int		set_forks(t_table *table);
void		*do_routine(void *param);
void		free_table(t_table *table);
//------------------------------------------------UTILS
long		ft_atoi(const char *str);

#endif
