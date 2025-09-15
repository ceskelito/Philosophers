/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:05:55 by rceschel          #+#    #+#             */
/*   Updated: 2025/09/15 16:47:59 by rceschel         ###   ########.fr       */
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

// Init with basis information wich can be used as a template for every philo.
// ID and semaphores need to be setted in the specific philo's process.
bool	initialize_philos_template(t_philo *philo, long int *rules)
{
	philo->id = 0;
	set_rules(philo, rules);
	philo->meals_eaten = 0;
	philo->last_meal = get_current_time();
	philo->start_time = get_current_time();
	philo->forks = NULL;
	philo->sem_write = NULL;
	return (true);
}

// Set the varibles of program structure
bool	initialize_program(t_program *program, t_philo *philos_template)
{
	int	i;

	program->philos_template = philos_template;
	program->philos_pid = malloc(program->rules[e_num_of_philos] * sizeof(int));
	if (!program->philos_pid)
		return (false);
	i = 0;
	while (i < program->rules[e_num_of_philos])
	{
		program->philos_pid[i] = 1;
		i++;
	}
	return (true);
}
