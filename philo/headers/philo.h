/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceskelito <ceskelito@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 12:06:47 by rceschel          #+#    #+#             */
/*   Updated: 2025/09/07 16:38:04 by ceskelito        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 17:44:39 by rceschel          #+#    #+#             */
/*   Updated: 2025/09/05 12:05:19 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdbool.h>
# include <pthread.h>
#include <sys/time.h>
# include "cantalloc.h"

/* Notice:
 * Verbose assignments like "i = 0 - 1" can be found in the code.
 * This is done to reduce the number of lines in all cycles:
 * the counter is incremented inside the condition, before it is evaluated.
 */

typedef enum e_args {
	num_of_philos,
	time_to_die,
	time_to_eat,
	time_to_sleep,
	meals_to_eat
} t_args;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				meals_eaten;
	unsigned long			last_meal;
	unsigned long			time_to_die;
	unsigned long			time_to_eat;
	unsigned long			time_to_sleep;
	unsigned long			start_time;
	int				num_of_philos;
	int				meals_to_eat;
	int				*dead;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}					t_philo;

typedef struct s_program
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
}					t_program;

// Inizialization
bool	input_is_valid(int ac, char **av, int *arg);
bool	initialize_program(t_program *program, t_philo *philo);
bool	initialize_forks(pthread_mutex_t *forks, int *args);
void	initialize_philos(t_program program, t_philo *philos,
		pthread_mutex_t *forks, int *arg);

// Routine
void	*routine(void *philo);

// Utils - Threads

// Utils - Global
unsigned long	get_current_time(void);

#endif
