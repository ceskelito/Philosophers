/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 14:37:51 by rceschel          #+#    #+#             */
/*   Updated: 2025/09/10 18:30:57 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thread_create(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->num_of_philos)
	{
		if (pthread_create(&philos[i].thread, NULL, &routine, &philos[i]) != 0)
		{
			while (--i >= 0)
				pthread_join(philos[i].thread, NULL);
			return ;
		}
		i++;
	}
//	i = 0;
//	while (i < philos->num_of_philos)
//	{
//		pthread_detach(philos[i].thread);
//		i++;
//	}
	monitor(philos);
		pthread_mutex_lock(philos->write_lock);
		ft_write(1, "Monitor exited\n\0");
		pthread_mutex_unlock(philos->write_lock);
	i = 0;
	pthread_mutex_destroy(philos->write_lock);
	pthread_mutex_destroy(philos->meal_lock);
	pthread_mutex_destroy(philos->dead_lock);
	while (i < philos->num_of_philos)
	{
		printf("Joining %i\n", i);
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}
