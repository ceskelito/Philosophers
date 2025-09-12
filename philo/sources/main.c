/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:15:16 by rceschel          #+#    #+#             */
/*   Updated: 2025/09/12 11:11:25 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_program		program;
	t_philo			*philos;
	pthread_mutex_t	*forks;

	--argc;
	++argv;
	if (!input_is_valid(argc, argv, program.rules))
		return(-1);
	philos = malloc(sizeof(t_philo) * program.rules[e_num_of_philos]);
	if (!philos)
		return (-1);
	forks = malloc(sizeof(pthread_mutex_t) * program.rules[e_num_of_philos]);
	if (!forks)
		return (free(philos), -1);
	initialize_program(&program, philos);
	initialize_forks(forks, program.rules);
	initialize_philos(&program, philos, forks);
	thread_create(philos);
	pthread_mutex_destroy(philos->write_lock);
	pthread_mutex_destroy(philos->meal_lock);
	pthread_mutex_destroy(philos->dead_lock);
	
	return (free(forks), free(philos), 0);
}
