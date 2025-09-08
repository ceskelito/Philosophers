/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 12:14:08 by rceschel          #+#    #+#             */
/*   Updated: 2025/09/08 17:15:40 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *pointer)
{
	int				i;
	t_philo			*philos;
	unsigned long	curtime;

	philos = (t_philo *)pointer;
	while (1)
	{
		if (*philos->dead == 1)
			return (NULL);
		i = 0 - 1;
		while (++i < philos->num_of_philos)
		{	
			if (philos[i].meals_eaten == philos->meals_to_eat)
				return (NULL);	
			curtime = get_current_time();
			if (curtime - philos[i].last_meal >= philos->time_to_die)
			{
				pthread_mutex_lock(philos->write_lock);
				print_message(curtime, philos, "died");
				pthread_mutex_unlock(philos->write_lock);
				pthread_mutex_lock(philos->dead_lock);
				*philos->dead = 1;
				pthread_mutex_unlock(philos->dead_lock);
				return (NULL);
			}

		}
	}
	return (NULL);
}

int	thread_create(t_program *program, pthread_mutex_t *forks)
{
	int			i;
	pthread_t	observer;

	i = 0 - 1;
	while (++i < program->philos->num_of_philos)
		if (pthread_create(&program->philos[i].thread, NULL, &routine, &program->philos[i]) != 0)
			clean_resources("Thread creation error", program, forks);
	if (pthread_create(&observer, NULL, &monitor, program->philos) != 0)
		clean_resources("Thread creation error", program, forks);
	if (pthread_join(observer, NULL) != 0)
		clean_resources("Thread join error", program, forks);
	i = 0 - 1;
	while (++i < program->philos->num_of_philos)
		if (pthread_join(program->philos[i].thread, NULL) != 0)
			clean_resources("Thread join error", program, forks);
	return (0);
}
