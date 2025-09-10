/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 16:00:13 by rceschel          #+#    #+#             */
/*   Updated: 2025/09/10 18:30:04 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_think(t_philo *philo)
{
	print_message(get_current_time(), philo, "is thinking");
}

static void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	print_message(get_current_time(), philo, "has taken a fork");
	pthread_mutex_lock(philo->r_fork);
	print_message(get_current_time(), philo, "has taken a fork");
	pthread_mutex_lock(philo->meal_lock);
	philo->eating = 1;
	print_message(get_current_time(), philo, "is eating");
	usleep(philo->time_to_eat);
	philo->meals_eaten += 1;
	philo->eating = 0;
	pthread_mutex_unlock(philo->meal_lock);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

static void	philo_sleep(t_philo *philo)
{
	print_message(get_current_time(), philo, "is sleeping");
	usleep(philo->time_to_sleep);
}

void	*routine(void *pointer)
{
	t_philo *philo = pointer;
	while (!is_someone_dead(philo))
	{
		philo_think(philo);
		philo_eat(philo);
		philo_sleep(philo);
	}
	return (NULL);
}

