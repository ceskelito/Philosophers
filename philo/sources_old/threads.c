/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 12:14:08 by rceschel          #+#    #+#             */
/*   Updated: 2025/09/09 12:48:18 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	*monitor(void *pointer)
{
	int				i;
	t_philo			*philos;
	unsigned long	curtime;

	//philos = ccantalloc(sizeof(pointer), 1);
	philos = (t_philo *)pointer;
	i = 0;
	while (1)
	{	
		curtime = get_current_time();
		if (*philos->dead == 1)
			break;
		if (curtime - philos[i].last_meal >= philos->time_to_die)
		{
			print_message(curtime, philos, "died");
			*philos->dead = 1;
			break;
		}
		if (philos[i].meals_eaten == philos->meals_to_eat)
			break;
		if((++i), i == philos->num_of_philos)
			i = 0;
	}
	return (NULL);
}

int	thread_create(t_program *program, pthread_mutex_t *forks)
{
	int			i;
	//pthread_t	observer;

	i = 0;
	while (i < program->philos->num_of_philos)
	{
		if (pthread_create(&program->philos[i].thread, NULL, &routine, &program->philos[i]) != 0)
			clean_resources("Thread creation error", program, forks);
		i++;
	}
	//if (pthread_create(&observer, NULL, &monitor, program->philos) != 0)
		///clean_resources("Thread creation error", program, forks);
	monitor(program->philos);
//	if (pthread_join(observer, NULL) != 0)
//		clean_resources("Thread join error", program, forks);
	i = 0;
	while (i < program->philos->num_of_philos)
	{
		if (pthread_join(program->philos[i].thread, NULL) != 0)
			clean_resources("Thread join error", program, forks);
		i++;
	}
	return (0);
}
