/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:08:01 by rceschel          #+#    #+#             */
/*   Updated: 2025/12/01 13:16:30 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Philosopher thinking action
static inline void	philo_think(t_philo *philo)
{
	print_message(get_current_time() - philo->start_time, philo,
		"is thinking");
}

// Philosopher sleeping action
static inline void	philo_sleep(t_philo *philo)
{
	print_message(get_current_time() - philo->start_time, philo,
		"is sleeping");
	ft_usleep(philo->time_to_sleep);
}

// Philosopher eating action
static void	philo_eat(t_philo *philo)
{
	sem_wait(philo->forks);
	print_message(get_current_time() - philo->start_time, philo,
		"has taken a fork");
	sem_wait(philo->forks);
	print_message(get_current_time() - philo->start_time, philo,
		"has taken a fork");
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = get_current_time();
	philo->meals_eaten += 1;
	pthread_mutex_unlock(&philo->meal_lock);
	print_message(get_current_time() - philo->start_time, philo, "is eating");
	ft_usleep(philo->time_to_eat);
	if (philo->meals_to_eat != -1 && philo->meals_eaten == philo->meals_to_eat)
		sem_post(philo->eat_sem);
	sem_post(philo->forks);
	sem_post(philo->forks);
}

// Main philosopher routine
void	routine(t_philo *philo)
{
	pthread_create(&philo->monitor, NULL, check_last_meal, philo);
	pthread_detach(philo->monitor);
	if (philo->id % 2 == 0)
		ft_usleep(philo->time_to_eat / 2);
	while (1)
	{
		philo_think(philo);
		philo_eat(philo);
		philo_sleep(philo);
	}
}
