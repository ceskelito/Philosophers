/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:05:55 by rceschel          #+#    #+#             */
/*   Updated: 2025/09/17 12:49:11 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Copy the program rules to the philosopher's attributes
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
	sem_unlink("/forks");
	sem_unlink("/write");
	sem_unlink("/eat");
	sem_unlink("/dead");
	if (sem && sem != SEM_FAILED)
	{
		sem_wait(sem);
		ft_write(2, str);
		sem_post(sem);
	}
	else
		ft_write(2, str);
}

// Initialize the philosopher with semaphores and mutexes
bool	initialize_philo(t_philo *philo, long int *rules, int id)
{
	int	n_philos;

	n_philos = rules[e_num_of_philos];
	philo->id = id;
	set_rules(philo, rules);
	philo->meals_eaten = 0;
	philo->last_meal = get_current_time();
	philo->start_time = philo->last_meal;
	philo->forks = sem_open("/forks", O_CREAT, 0666, n_philos);
	philo->write_sem = sem_open("/write", O_CREAT, 0666, 1);
	philo->eat_sem = sem_open("/eat", O_CREAT, 0666, 0);
	philo->dead_sem = sem_open("/dead", O_CREAT, 0666, 1);
	if (philo->forks == SEM_FAILED || philo->write_sem == SEM_FAILED
		|| philo->eat_sem == SEM_FAILED || philo->dead_sem == SEM_FAILED)
	{
		print_error("Failed init semaphores\n", NULL);
		return (false);
	}
	if (pthread_mutex_init(&philo->meal_lock, NULL) != 0)
	{
		print_error("Failed init meal_lock\n", philo->write_sem);
		return (false);
	}
	return (true);
}

// Initialize the program structure variables and process IDs
bool	initialize_program(t_program *program)
{
	int	i;

	sem_unlink("/eat");
	sem_unlink("/write");
	sem_unlink("/forks");
	sem_unlink("/dead");
	program->eat_sem = sem_open("/eat", O_CREAT, 0666, 0);
	program->write_sem = sem_open("/write", O_CREAT, 0666, 1);
	program->dead_sem = sem_open("/dead", O_CREAT, 0666, 1);
	if (program->write_sem == SEM_FAILED || program->eat_sem == SEM_FAILED
		|| program->dead_sem == SEM_FAILED)
		return (false);
	program->philos_pid = malloc(program->rules[e_num_of_philos] * sizeof(int));
	if (!program->philos_pid)
		return (false);
	i = 0;
	while (i < program->rules[e_num_of_philos])
	{
		program->philos_pid[i] = 0;
		i++;
	}
	return (true);
}
