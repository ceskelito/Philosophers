/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 12:06:47 by rceschel          #+#    #+#             */
/*   Updated: 2025/09/08 17:59:23 by rceschel         ###   ########.fr       */
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
# include <sys/time.h>
# include <unistd.h>
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

typedef struct	s_philo
{
	pthread_t				thread;
	int						id;
	_Atomic int				eating;
	_Atomic int				meals_eaten;
	_Atomic	unsigned long	last_meal;
	unsigned long			time_to_die;
	unsigned long			time_to_eat;
	unsigned long			time_to_sleep;
	unsigned long			start_time;
	int						num_of_philos;
	int						meals_to_eat;
	_Atomic int				*dead;
	pthread_mutex_t			*r_fork;
	pthread_mutex_t			*l_fork;
	pthread_mutex_t			*write_lock;
	pthread_mutex_t			*dead_lock;
	pthread_mutex_t			*meal_lock;
}				t_philo;

typedef struct s_program
{
	_Atomic int		dead_flag;
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

// Utils 
void			ft_write(int fd, char *str);
void			clean_resources(char *msg, t_program *program, pthread_mutex_t *forks);
void			print_message(unsigned long time, t_philo *philo, char *message);
unsigned long	get_current_time(void);

// Thread
int	thread_create(t_program *program, pthread_mutex_t *forks);

#endif
