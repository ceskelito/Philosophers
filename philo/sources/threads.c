/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 11:35:19 by rceschel          #+#    #+#             */
/*   Updated: 2025/09/10 13:02:05 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 11:14:40 by rceschel          #+#    #+#             */
/*   Updated: 2025/09/10 11:32:30 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *pointer)
{
	if(pointer)
		return (NULL);
	return (NULL);
}

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
	i = 0;
	while (i < philos->num_of_philos)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}
