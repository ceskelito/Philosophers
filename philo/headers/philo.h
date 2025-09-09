/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 14:40:32 by rceschel          #+#    #+#             */
/*   Updated: 2025/09/09 18:05:39 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
//# include "cantalloc.h"

# define MAX_ARGS 5

typedef unsigned long ulong;

typedef enum e_args {
	e_num_of_philos,
	e_time_to_die,
	e_time_to_eat,
	e_time_to_sleep,
	e_meals_to_eat
} t_args;

typedef struct	s_philo
{
	pthread_t				thread;
	int						id;
	unsigned long			rules[MAX_ARGS];
	unsigned long			start_time;
	_Atomic int				eating;
	_Atomic unsigned long	last_meal;
	_Atomic int				meals_eaten;
	_Atomic int				*dead;
	pthread_mutex_t			*r_fork;
	pthread_mutex_t			*l_fork;
	pthread_mutex_t			*write_lock;
	pthread_mutex_t			*dead_lock;
	pthread_mutex_t			*meal_lock;
}				t_philo;
	
typedef struct s_program
{
	unsigned long	rules[MAX_ARGS];
	_Atomic int		dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
}					t_program;


// Input
bool	input_is_valid(int argc, char **argv, unsigned long *rules);

// Init
bool	initialize_program(t_program *program, t_philo *philos);
bool	initialize_forks(pthread_mutex_t *forks, unsigned long *rules);
void	initialize_philos(t_program *program, t_philo *philos, pthread_mutex_t *forks);

// Utils
unsigned long	get_current_time(void);
#endif
