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

// Check if philo is starving and set the dead flag
static void	*check_last_meal(void *pointer)
{
	t_philo *philo;
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
			printf("%lu %i %s\n", get_current_time() - philo->start_time,
				philo->id, "died");
			sem_post(philo->write_sem);
			exit(1);
		}
	}
	return (NULL);
}

static void	philo_think(t_philo *philo)
{
	print_message(get_current_time() - philo->start_time, philo, "is thinking");
}


static void	philo_eat(t_philo *philo)
{
	sem_wait(philo->forks);
	print_message(get_current_time() - philo->start_time, philo,
		"has taken a fork");
	sem_wait(philo->forks);
	print_message(get_current_time() - philo->start_time, philo,
		"has taken a fork");
	pthread_mutex_lock(&philo->meal_lock);
	print_message(get_current_time() - philo->start_time, philo, "is eating");
	ft_usleep(philo->time_to_eat);
	philo->meals_eaten += 1;
	if (philo->meals_eaten == philo->meals_to_eat)
		sem_post(philo->eat_sem);
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(&philo->meal_lock);
	sem_post(philo->forks);
	sem_post(philo->forks);
}

static void	philo_sleep(t_philo *philo)
{
	print_message(get_current_time() - philo->start_time, philo, "is sleeping");
	ft_usleep(philo->time_to_sleep);
}

void	routine(t_philo *philo)
{
	pthread_create(&philo->monitor, NULL, check_last_meal, philo);
	pthread_detach(philo->monitor);
	while (1)
	{
		philo_think(philo);
		philo_eat(philo);
		philo_sleep(philo);
	}
}
