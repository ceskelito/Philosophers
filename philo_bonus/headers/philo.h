/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:20:35 by rceschel          #+#    #+#             */
/*   Updated: 2025/09/15 18:30:56 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <fcntl.h>		/* For O_* constants */
# include <sys/stat.h>	/* For mode constants */
# include <semaphore.h>
# include <sys/types.h>
# include <signal.h>
#include <sys/wait.h>

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
	int		id;

	int		num_of_philos;
	t_time	time_to_die;
	t_time	time_to_eat;
	t_time	time_to_sleep;
	int		meals_to_eat;

	int		meals_eaten;
	t_time	last_meal;
	t_time	start_time;
	
	sem_t	*forks;
	sem_t	*sem_write;
}	t_philo;

typedef struct s_program
{
	long int		rules[MAX_ARGS];
	t_philo			*philos_template;
	int				*philos_pid;
	
}	t_program;

// Input
bool	input_is_valid(int argc, char **argv, long int *rules);
int		ft_usleep(size_t milliseconds);

// Init
bool	initialize_program(t_program *program, t_philo *philos_template);
bool	initialize_philos_template(t_philo *philos_template, long int *rules);

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
