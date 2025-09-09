/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 12:06:40 by rceschel          #+#    #+#             */
/*   Updated: 2025/09/09 17:22:48 by rceschel         ###   ########.fr       */
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
	int	i;

	i = 0;
	while (i < args[num_of_philos])
	{
		philos[i].id = i + 1;
		philos[i].eating = 0;
		philos[i].meals_eaten = 0;
		philos[i].last_meal = get_current_time();
		philos[i].start_time = get_current_time();
		philos[i].dead = &program.dead_flag;
		philos[i].write_lock = &program.write_lock;
		write(1, "a\n", 2);
		philos[i].dead_lock = &program.dead_lock;
		philos[i].meal_lock = &program.meal_lock;
		philos[i].r_fork = &forks[i];
		if (i == 0)
			philos[i].r_fork = &forks[philos->num_of_philos - 1];
		else
			philos[i].l_fork = &forks[i - 1];
		set_parameters(&philos[i], args);
		i++;
	}
}

// Initialize forks mutexes
bool	initialize_forks(pthread_mutex_t *forks, int *args)
{
	int	i;

	i = 0;
	while (i < args[num_of_philos])
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			return (false);
		i++;
	}
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
