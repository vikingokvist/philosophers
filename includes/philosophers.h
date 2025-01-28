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
# define PHILOS_MAX 200
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>

typedef struct s_table
{
	int	philosophers_count;
	int	time_to_eat;
	int	time_to_die;
	int	time_to_sleep;
	int	meals_to_have;
	int	someone_died;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_lock;
}	t_table;

typedef struct s_philo
{
	pthread_t	thread;
	int		id;
	int		meals_had;
	int		last_meal;
	int		is_eating;
	int		time_alive;
	t_table	*table;
}	t_philo;


//-----------------------------------------------SRC
int		main(int argc, char **argv);
void	print_message(int *id, char *string, int time_to_sleep);
int		check_valid_values(int argc, char **argv);
void	init_table(t_table *table, char **argv, pthread_mutex_t *forks);
int		init_forks(t_table *table);
void	init_philos(t_table *table, t_philo *philos);
int		create_threads(t_philo *philos);
void	*do_routine(void *param);
void	free_table(t_philo *philos);
int		get_time(void);
int		someone_has_died(t_philo *philo);
int		had_all_meals(t_philo *philo);
//------------------------------------------------UTILS
long		ft_atoi(const char *str);
char		*philosopher_name(int i);

#endif
