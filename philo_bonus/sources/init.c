/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:05:55 by rceschel          #+#    #+#             */
/*   Updated: 2025/09/16 16:46:41 by rceschel         ###   ########.fr       */
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

static void	print_error(char *str, sem_t *sem)
{
	sem_wait(sem);
	ft_write(2, str);
	sem_post(sem);
}

// Init the philo with sems and mutexes
bool	initialize_philo(t_philo *philo, long int *rules, int id)
{
	int	n_philos;

	n_philos = rules[e_num_of_philos];
	philo->id = id;
	set_rules(philo, rules);
	philo->meals_eaten = 0;
	philo->last_meal = get_current_time();
	philo->start_time = get_current_time();
	philo->forks = sem_open("/forks", O_CREAT, 0666, n_philos);
	philo->write_sem = sem_open("/write", O_CREAT, 0666, 1);
	philo->eat_sem = sem_open("/eat", O_CREAT, 0666, 0);

	if (philo->forks == SEM_FAILED || 
		philo->write_sem == SEM_FAILED || 
		philo->eat_sem == SEM_FAILED)	
	{
		sem_unlink("/forks");
        sem_unlink("/write");
        sem_unlink("/eat");
		print_error("Failed init semaphores\n\0", philo->write_sem);
		return (false);
	}
	if (pthread_mutex_init(&philo->meal_lock, NULL) != 0)
	{
		print_error("Failed init meal_lock\n\0", philo->write_sem);
		return (false);
	}
	if (pthread_mutex_init(&philo->dead_lock, NULL) != 0)
	{
		print_error("Failed init dead_lock\n\0", philo->write_sem);
		return (false);
	}
	return (true);
}

// Set the varibles of program structure
// Init pids to a positive value
bool	initialize_program(t_program *program)
{
	int	i;
	
	sem_unlink("/eat");
	sem_unlink("/write");
	sem_unlink("/forks");
	program->eat_sem = sem_open("/eat", O_CREAT, 0666, 0);
	program->write_sem = sem_open("/write", O_CREAT, 0666, 1);
	if (program->write_sem == SEM_FAILED)
		return (false);
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
