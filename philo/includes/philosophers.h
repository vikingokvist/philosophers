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

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>

# define PHILOS_MAX 200
# define ERR_ARGS "Usage:\n  ./philo <number_of_philosopher> <time_to_die> %s"
# define ERR_ARGS2 "<time_to_eat> <time_to_sleep> [meals_to_have]\n"
# define ERR_ARGS_VALID "Values must be digits from 0 to UINT_MAX\n"
# define ERR_ARGS_PHILO_MAX "<number_of_philosopher> cannot exceed 200\n"
# define ERR_THREAD_CREATE "Failed to create thread.\n"
# define ERR_THREAD_JOIN "Failed joining threads.\n"
# define ERR_MUTEX_INIT "Failed to initialize mutex\n"
# define ERR_TIME "Error getting time\n"
# define MSG_SLEEP "is sleeping"
# define MSG_THINK "is thinking"
# define MSG_EAT "is eating"
# define MSG_FORK "has taken a fork"
# define MSG_DEATH "died"
# define MSG_DONE "finished eating"

typedef struct s_table
{
	int				philosophers_count;
	int				someone_died;
	size_t				had_all_meals;
	pthread_t		table_thread;
	pthread_mutex_t	*forks;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	r_fork;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	dead_lock;
}	t_table;

typedef struct s_philo
{
	size_t				id;
	size_t				time_to_eat;
	size_t				time_to_die;
	size_t				time_to_sleep;
	size_t				meals_to_have;
	size_t				is_eating;
	size_t				meals_had;
	size_t				start_time;
	size_t				last_meal;
	pthread_t			thread;
	t_table				*table;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		*write_lock;
	pthread_mutex_t		*meal_lock;
	pthread_mutex_t		*dead_lock;
}	t_philo;

//-----------------------------------------------INIT
int		main(int argc, char **argv);
int		check_valid_values(char **argv);
int		init_table(t_table *table, pthread_mutex_t *forks, char **argv);
void	init_philos(t_table *table, t_philo *philos, char **argv,
			size_t start_time);
int		create_threads(t_philo *philos);
//-----------------------------------------------PHILO ROUTINE
void	*philo_routine(void *param);
void	status_msg(t_philo *philo, size_t *id, char *string);
void	ph_eat(t_philo *philo);
int		someone_died(t_philo *philo);
//-----------------------------------------------PHILO ROUTINE
void	*table_routine(void *param);
int		all_finished_eating(t_philo *philo);
//------------------------------------------------UTILS
void	ft_usleep(size_t time_to_usleep);
size_t	get_time(void);
long	ft_atol(const char *str);
int		ft_isdigit(int c);
void	free_table(t_philo *philo);

#endif
