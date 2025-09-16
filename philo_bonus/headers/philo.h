/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:20:35 by rceschel          #+#    #+#             */
/*   Updated: 2025/09/16 16:42:30 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define MAX_ARGS 5

typedef unsigned long				t_time;

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
	int							id;

	int							num_of_philos;
	t_time						time_to_die;
	t_time						time_to_eat;
	t_time						time_to_sleep;
	int							meals_to_eat;

	int							meals_eaten;
	t_time						last_meal;
	t_time						start_time;

	sem_t						*forks;
	sem_t						*write_sem;
	sem_t						*eat_sem;
	// Limit concurrent fork acquisition to avoid deadlock
	sem_t						*limit;

	pthread_t					monitor;
	pthread_mutex_t				meal_lock;
}t_philo;

typedef struct s_program
{
	long int					rules[MAX_ARGS];
	int							*philos_pid;

	sem_t						*write_sem;
	sem_t						*eat_sem;

	pthread_t					meal_monitor;
}t_program;

// Input
bool	input_is_valid(int argc, char **argv, long int *rules);
int		ft_usleep(size_t milliseconds);

// Init
bool	initialize_program(t_program *program);
bool	initialize_philo(t_philo *philos_template, long int *rules, int id);

// Utils
t_time	get_current_time(void);
void	ft_write(int fd, char *str);
void	print_message(t_time time, t_philo *philo, char *message);

// Threads
void	routine(t_philo *philo);
void	*have_philos_ate(void *param);

#endif
