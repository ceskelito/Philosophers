/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 11:35:03 by rceschel          #+#    #+#             */
/*   Updated: 2025/09/10 13:03:26 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Check if a philo need to die for starving and set the dead_flag
// The needed mutexes are locked before the function call
static void	check_last_meal(t_philo *philos)
{
	int		i;
	t_time	tmp;

	i = 0;
	while (i < philos->num_of_philos)
	{
		tmp = get_current_time() - philos[i].last_meal; 
		if (tmp >= philos->time_to_die && philos[i].eating == 0)
		{
			*philos->dead = 1;
			print_message(get_current_time(), &philos[i], "died");
			return ;
		}
		i++;
	}
}

// Check the dead_flag after a call to check_last_meal()
static int	is_someone_dead(t_philo *philos)
{
	int	dead;

	dead = 0;
	pthread_mutex_lock(philos->dead_lock);
	pthread_mutex_lock(philos->meal_lock);
	check_last_meal(philos);
	if(*philos->dead)
		dead = 1;
	pthread_mutex_unlock(philos->dead_lock);
	pthread_mutex_unlock(philos->meal_lock);
	return (dead);
}

// Check if all philos have eaten meals_to_eat meals
static int	have_philos_ate(t_philo *philos)
{
	int	i;

	if (philos->meals_to_eat == -1)
		return (0);
	i = 0;
	while (i < philos->meals_to_eat)
	{
		pthread_mutex_lock(philos->meal_lock);
		if (philos[i].meals_eaten < philos->meals_to_eat)
			return (0);
		pthread_mutex_unlock(philos->meal_lock);
		i++;
	}
	return (1);
}

void	monitor(t_philo *philos)
{
	while(1)
	{
		if (is_someone_dead(philos) || have_philos_ate(philos))
				return ;
	}
}
