/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 14:37:51 by rceschel          #+#    #+#             */
/*   Updated: 2025/09/10 16:48:21 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thread_create(t_philo *philos)
{
	int	i;
	int	failure;

	i = 0;
	while (i < philos->num_of_philos)
	{
		failure = pthread_create(&philos[i].thread, NULL, &routine, &philos[i]);
		if (failure)
		{
			while (--i >= 0)
				pthread_join(philos[i].thread, NULL);
			return ;
		}
		i++;
	}
	monitor(philos);
		pthread_mutex_lock(philos->write_lock);
		ft_write(1, "Monitor exited\n\0");
		pthread_mutex_unlock(philos->write_lock);
	i = 0;
	while (i < philos->num_of_philos)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}
