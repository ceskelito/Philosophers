/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:08:01 by rceschel          #+#    #+#             */
/*   Updated: 2025/09/16 16:39:07 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

// Monitor thread to check if philosopher is starving
static void	*check_last_meal(void *pointer)
{
	t_philo	*philo;
	t_time	time_from_meal;

	philo = pointer;
	while (1)
	{
		pthread_mutex_lock(&philo->meal_lock);
		time_from_meal = get_current_time() - philo->last_meal;
		pthread_mutex_unlock(&philo->meal_lock);
		if (time_from_meal >= philo->time_to_die)
		{
			sem_wait(philo->write_sem);
			printf("%lu %i died\n", get_current_time() - philo->start_time,
				philo->id);
			exit(1);
		}
		usleep(1000);
	}
	return (NULL);
}

// Philosopher thinking action
static void	philo_think(t_philo *philo)
{
	print_message(get_current_time() - philo->start_time, philo,
		"is thinking");
}

// Philosopher eating action
static void	philo_eat(t_philo *philo)
{
	// Limit concurrent attempts to acquire forks
	sem_wait(philo->limit);
	sem_wait(philo->forks);
	print_message(get_current_time() - philo->start_time, philo,
		"has taken a fork");
	sem_wait(philo->forks);
	print_message(get_current_time() - philo->start_time, philo,
		"has taken a fork");
	// Release limiter once both forks are taken
	sem_post(philo->limit);
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = get_current_time();
	print_message(get_current_time() - philo->start_time, philo, "is eating");
	pthread_mutex_unlock(&philo->meal_lock);
	ft_usleep(philo->time_to_eat);
	philo->meals_eaten += 1;
	if (philo->meals_to_eat != -1 && philo->meals_eaten == philo->meals_to_eat)
		sem_post(philo->eat_sem);
	sem_post(philo->forks);
	sem_post(philo->forks);
}

// Philosopher sleeping action
static void	philo_sleep(t_philo *philo)
{
	print_message(get_current_time() - philo->start_time, philo,
		"is sleeping");
	ft_usleep(philo->time_to_sleep);
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
