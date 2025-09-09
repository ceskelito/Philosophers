/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:05:55 by rceschel          #+#    #+#             */
/*   Updated: 2025/09/09 18:14:29 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_rules(unsigned long *target, unsigned long *rules)
{
	int	i;

	i = 0;
	while (i < MAX_ARGS)
	{
		target[i] = rules[i];
//		printf("target: %lu\nrule: %lu\n", target[i], rules[i]);
		i++;
	}
}

void	initialize_philos(t_program *program, t_philo *philos,
		pthread_mutex_t *forks)
{
	unsigned long	i;

	i = 0;
	while (i < program->rules[e_num_of_philos])
	{
		philos[i].id = i + 1;
		set_rules(philos[i].rules, program->rules);
//		printf("ID: %i\n", philos[i].id);
//		for(int j = 0; j < MAX_ARGS; j++)
//			printf("R n. %i: %lu\n", j, philos->rules[j]);
		philos[i].eating = 0;
		philos[i].meals_eaten = 0;
		philos[i].last_meal = get_current_time();
		philos[i].start_time = get_current_time();
		philos[i].dead = &program->dead_flag;
		philos[i].write_lock = &program->write_lock;
		philos[i].dead_lock = &program->dead_lock;
		philos[i].meal_lock = &program->meal_lock;
		philos[i].r_fork = &forks[i];
		if (i == 0)
			philos[i].r_fork = &forks[philos->rules[e_num_of_philos] - 1];
		else
			philos[i].l_fork = &forks[i - 1];
		i++;
	}
}

bool	initialize_forks(pthread_mutex_t *forks, unsigned long *rules)
{
	unsigned long	i;

	i = 0;
	while (i < rules[e_num_of_philos])
	{
		if (pthread_mutex_init(forks + i, NULL) != 0)
			return (free(forks), false);
		i++;
	}
	return (true);
}

bool	initialize_program(t_program *program, t_philo *philos)
{
	program->dead_flag = 0;
	program->philos = philos;
	return (pthread_mutex_init(&program->dead_lock, NULL) == 0
		&& pthread_mutex_init(&program->meal_lock, NULL) == 0
		&& pthread_mutex_init(&program->write_lock, NULL) == 0);
}
