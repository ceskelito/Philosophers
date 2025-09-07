/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceskelito <ceskelito@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 17:12:35 by rceschel          #+#    #+#             */
/*   Updated: 2025/09/07 16:37:06 by ceskelito        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	int				args[5];
	int				i;
	t_program		program;
	t_philo			*philos;
	pthread_mutex_t	*forks;


	args[0] = 0;
	philos = cantalloc(sizeof(t_philo) * args[num_of_philos]);
	forks = cantalloc(sizeof(pthread_mutex_t) * args[num_of_philos]);
	if (!philos)
		return (cantalloc_clean(), -1);
	if (!input_is_valid(ac, av, args))
		return (cantalloc_clean(), -1);
	if (!initialize_program(&program, philos) || !initialize_forks(forks, args))
		return (cantalloc_clean(), -1);
	printf("program inizialized\n"); //DEBUG
	initialize_philos(program, philos, forks, args);
	i = 0 - 1;
	while (++i < philos->num_of_philos)
		pthread_create(&philos[i].thread, NULL, &routine, (t_philo *)&philos[i]);
	pthread_join(philos[0].thread, NULL);
	cantalloc_clean();
	return (0);
}
