/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:05:55 by rceschel          #+#    #+#             */
/*   Updated: 2025/09/12 15:29:39 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Copies the program rules in the respective philo's attributes
static void	set_rules(t_philo *philo, long int *rules)
{
	philo->num_of_philos = rules[e_num_of_philos];
	philo->time_to_die = rules[e_time_to_die];
	philo->time_to_eat = rules[e_time_to_eat];
	philo->time_to_sleep = rules[e_time_to_sleep];
	philo->meals_to_eat = rules[e_meals_to_eat];
}

// For every philo:
//
// Set the philo's ID, initalize the attributes, call set_rules(),
// and point the pointers to the program's locks and forks mutexes
bool	initialize_philos(t_program *program, t_philo *philos,
		pthread_mutex_t *forks)
{
	long int	i;

	i = 0;
	while (i < program->rules[e_num_of_philos])
	{
		philos[i].id = i + 1;
		set_rules(&philos[i], program->rules);
		philos[i].meals_eaten = 0;
		philos[i].last_meal = get_current_time();
		philos[i].start_time = get_current_time();
		philos[i].dead = &program->dead_flag;
		philos[i].write_lock = &program->write_lock;
		philos[i].dead_lock = &program->dead_lock;
		if (pthread_mutex_init(&philos[i].meal_lock, NULL) != 0)
			return (false);
		philos[i].r_fork = &forks[i];
		if (i == 0)
			philos[i].l_fork = &forks[philos->num_of_philos - 1];
		else
			philos[i].l_fork = &forks[i - 1];
		i++;
	}
	return (true);
}

// Initialize forks mutexes array
bool	initialize_forks(pthread_mutex_t *forks, long int *rules)
{
	long int	i;

	i = 0;
	while (i < rules[e_num_of_philos])
	{
		if (pthread_mutex_init(forks + i, NULL) != 0)
			return (free(forks), false);
		i++;
	}
	return (true);
}

// Set the varibles of program structure
bool	initialize_program(t_program *program, t_philo *philos)
{
	program->dead_flag = 0;
	program->philos = philos;
	return (pthread_mutex_init(&program->dead_lock, NULL) == 0
		&& pthread_mutex_init(&program->write_lock, NULL) == 0);
}
