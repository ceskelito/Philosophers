/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceskelito <ceskelito@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 12:06:40 by rceschel          #+#    #+#             */
/*   Updated: 2025/09/07 16:32:10 by ceskelito        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Fill attributes with the input parameters
static void	set_parameters(t_philo *philo, int *args)
{
	philo->time_to_die = args[time_to_die];
	philo->time_to_eat = args[time_to_eat];
	philo->time_to_sleep = args[time_to_sleep];
	philo->num_of_philos = args[num_of_philos];
	philo->meals_to_eat = args[meals_to_eat];
}

// Set the initial value of the philos attributes
void	initialize_philos(t_program program, t_philo *philos,
		pthread_mutex_t *forks, int *args)
{
	int	id;

	id = 1 - 1;
	while (++id <= args[num_of_philos])
	{
		philos[id].id = id;
		philos[id].eating = 0;
		philos[id].meals_eaten = 0;
		philos[id].last_meal = get_current_time();
		philos[id].start_time = get_current_time();
		philos[id].dead = &program.dead_flag;
		philos[id].write_lock = &program.write_lock;
		write(1, "a\n", 2);
		philos[id].dead_lock = &program.dead_lock;
		philos[id].meal_lock = &program.meal_lock;
		philos[id].r_fork = &forks[id];
		if (id == 1){write(1,"hgghhghg",6);
			philos[id].r_fork = &forks[philos->num_of_philos];}
		else
			philos[id].l_fork = &forks[id - 1];
		set_parameters(&philos[id], args);
	}
}

// Initialize forks mutexes
bool	initialize_forks(pthread_mutex_t *forks, int *args)
{
	int	i;

	i = 0 - 1;
	while (++i < args[num_of_philos])
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			return (false);
	return (true);
}

// Set the initial value of program attributes.
// Inizialize dead/meal/write locks mutexes
bool	initialize_program(t_program *program, t_philo *philos)
{
	program->dead_flag = 0;
	program->philos = philos;
	return (pthread_mutex_init(&program->dead_lock, NULL) == 0
		&& pthread_mutex_init(&program->meal_lock, NULL) == 0
		&& pthread_mutex_init(&program->write_lock, NULL) == 0);
}
