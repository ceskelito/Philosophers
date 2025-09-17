/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 11:35:03 by rceschel          #+#    #+#             */
/*   Updated: 2025/09/16 13:11:37 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdbool.h>

// Check if a philo is starving and set the dead_flag
static void	check_last_meal(t_philo *philos)
{
	int		i;
	t_time	time_tmp;

	i = 0;
	while (i < philos->num_of_philos)
	{
		pthread_mutex_lock(&philos[i].meal_lock);
		time_tmp = get_current_time() - philos[i].last_meal;
		pthread_mutex_unlock(&philos[i].meal_lock);
		if (time_tmp >= philos->time_to_die)
		{
			pthread_mutex_lock(philos->write_lock);
			pthread_mutex_lock(philos->dead_lock);
			*philos->dead = 1;
			printf("%lu %i %s\n", get_current_time() - philos->start_time,
				philos[i].id, "died");
			pthread_mutex_unlock(philos->dead_lock);
			pthread_mutex_unlock(philos->write_lock);
			break ;
		}
		i++;
	}
}

// Check if all philos have eaten meals_to_eat meals
static int	have_philos_ate(t_philo *philos)
{
	int	i;

	if (philos->meals_to_eat == -1)
		return (false);
	i = 0;
	while (i < philos->num_of_philos)
	{
		pthread_mutex_lock(&philos[i].meal_lock);
		if (philos[i].meals_eaten >= philos->meals_to_eat)
		{
			pthread_mutex_unlock(&philos[i].meal_lock);
			i++;
			continue ;
		}
		pthread_mutex_unlock(&philos[i].meal_lock);
		return (false);
	}
	pthread_mutex_lock(philos->dead_lock);
	*philos->dead = 1;
	pthread_mutex_unlock(philos->dead_lock);
	return (true);
}

void	monitor(t_philo *philos)
{
	while (1)
	{
		check_last_meal(philos);
		if (is_someone_dead(philos) || have_philos_ate(philos))
			return ;
	}
}
