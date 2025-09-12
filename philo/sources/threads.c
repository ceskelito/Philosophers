/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 14:37:51 by rceschel          #+#    #+#             */
/*   Updated: 2025/09/12 14:44:02 by rceschel         ###   ########.fr       */
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
			while (--i, i >= 0)
				pthread_join(philos[i].thread, NULL);
			return ;
		}
		i++;
	}

	monitor(philos);
	i = 0;
	while (i < philos->num_of_philos)
	{
		pthread_join(philos[i].thread, NULL);
		pthread_mutex_destroy(&philos[i].meal_lock);
		i++;
	}
	pthread_mutex_destroy(philos->write_lock);
	pthread_mutex_destroy(philos->dead_lock);
}
