/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 17:11:01 by rceschel          #+#    #+#             */
/*   Updated: 2025/09/09 12:02:14 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_think(t_philo *philo)
{
	print_message(get_current_time(), philo, "is thinking");
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	pthread_mutex_lock(philo->r_fork);
	pthread_mutex_lock(philo->meal_lock);
	print_message(get_current_time(), philo, "is eating");
	pthread_mutex_unlock(philo->meal_lock);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	philo_sleep(t_philo *philo)
{
	print_message(get_current_time(), philo, "is sleeping");
	usleep(philo->time_to_sleep);
}

void	*routine(void *pointer)
{
	t_philo			*philo;

	philo = (t_philo *) pointer;
	print_message(get_current_time(), philo, "start routine"); //DEBUG
	while(1)
	{
		philo_think(philo);
		philo_eat(philo);
		philo_sleep(philo);
	}
	return (NULL);
}
