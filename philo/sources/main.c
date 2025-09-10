/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:15:16 by rceschel          #+#    #+#             */
/*   Updated: 2025/09/10 14:36:25 by rceschel         ###   ########.fr       */
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
//	printf( "Rules:\n%lu\n%lu\n%lu\n%lu\n%lu\n",
//		program.rules[e_num_of_philos],
//		program.rules[e_time_to_die],
//		program.rules[e_time_to_eat],
//		program.rules[e_time_to_sleep],
//		program.rules[e_meals_to_eat]); // DEBUG
	philos = malloc(sizeof(t_philo) * program.rules[e_num_of_philos]);
	if (!philos)
		return (-1);
	forks = malloc(sizeof(pthread_mutex_t) * program.rules[e_num_of_philos]);
	if (!forks)
		return (free(philos), -1);
	initialize_program(&program, philos);
	initialize_forks(forks, program.rules);
	initialize_philos(&program, philos, forks);
	//printf("n:%lu\n", program.rules[e_num_of_philos]);
	//for (unsigned long i = 0; i < program.rules[e_num_of_philos]; i++)
	//	printf("%i\n", philos[i].id);
	thread_create(philos);
	
	return (free(forks), free(philos), 0);
}
