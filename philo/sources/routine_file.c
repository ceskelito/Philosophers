/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceskelito <ceskelito@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 17:11:01 by rceschel          #+#    #+#             */
/*   Updated: 2025/09/07 16:37:55 by ceskelito        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

static void	print_message(unsigned long time, int id, char *message)
{

		printf("%lu %i %s\n", time, id, message);
}

void *routine(void *pointer)
{
	unsigned long	curtime;
	t_philo			*philo;

	philo = (t_philo *) pointer;
	while(1)
	{
		curtime = get_current_time();
		if (*philo->dead == 1 || philo->meals_eaten == philo->meals_to_eat)
			return (NULL);
		if (curtime - philo->last_meal >= philo->time_to_die)
		{
			pthread_mutex_lock(philo->write_lock);
			print_message(curtime, philo->id, "died");
			pthread_mutex_unlock(philo->write_lock);
			pthread_mutex_lock(philo->dead_lock);
			*philo->dead = 1;
			pthread_mutex_unlock(philo->dead_lock);
			return (NULL);
		}
	}
}
