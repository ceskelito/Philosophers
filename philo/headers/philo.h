/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 14:40:32 by rceschel          #+#    #+#             */
/*   Updated: 2025/09/12 16:43:41 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>		// printf()
# include <stdbool.h>	// booleans
# include <pthread.h>	// threads and mutexes
# include <sys/time.h>	// gettimeofday()
# include <unistd.h>	// write()
# include <stdlib.h>	// malloc()

# define MAX_ARGS 5

typedef unsigned long	t_time;

typedef enum e_args
{
	e_num_of_philos,
	e_time_to_die,
	e_time_to_eat,
	e_time_to_sleep,
	e_meals_to_eat
}	t_args;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;

	int				num_of_philos;
	t_time			time_to_die;
	t_time			time_to_eat;
	t_time			time_to_sleep;
	int				meals_to_eat;

	t_time			start_time;
	t_time			last_meal;
	int				meals_eaten;
	int				*dead;

	pthread_mutex_t	meal_lock;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
}	t_philo;

typedef struct s_program
{
	long int		rules[MAX_ARGS];
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	//pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
}	t_program;

// Input
bool	input_is_valid(int argc, char **argv, long int *rules);
int		ft_usleep(size_t milliseconds);

// Init
bool	initialize_program(t_program *program, t_philo *philos);
bool	initialize_forks(pthread_mutex_t *forks, long int *rules);
bool	initialize_philos(t_program *program,
			t_philo *philos, pthread_mutex_t *forks);

// Utils
t_time	get_current_time(void);
void	ft_write(int fd, char *str);
void	print_message(t_time time, t_philo *philo, char *message);
int		is_someone_dead(t_philo *philos);

// Threads
void	*routine(void *pointer);
void	monitor(t_philo *philos);
void	thread_create(t_philo *philos);

#endif
