/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 16:00:13 by rceschel          #+#    #+#             */
/*   Updated: 2025/09/12 16:54:17 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_think(t_philo *philo)
{
	print_message(get_current_time() - philo->start_time, philo, "is thinking");
}

// Helper function to reduce the line number
static void	philo_eating_action(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_lock);
	print_message(get_current_time() - philo->start_time, philo, "is eating");
	ft_usleep(philo->time_to_eat);
	philo->meals_eaten += 1;
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(&philo->meal_lock);
}

static void	philo_eat(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	first = philo->l_fork;
	second = philo->r_fork;
	if (philo->id == 1)
	{
		first = philo->r_fork;
		second = philo->l_fork;
	}
	pthread_mutex_lock(first);
	print_message(get_current_time() - philo->start_time, philo,
		"has taken a fork");
	if (first == second)
	{
		pthread_mutex_unlock(first);
		ft_usleep(philo->time_to_die);
	}
	pthread_mutex_lock(second);
	print_message(get_current_time() - philo->start_time, philo,
		"has taken a fork");
	philo_eating_action(philo);
	pthread_mutex_unlock(second);
	pthread_mutex_unlock(first);
}

static void	philo_sleep(t_philo *philo)
{
	print_message(get_current_time() - philo->start_time, philo, "is sleeping");
	ft_usleep(philo->time_to_sleep);
}

void	*routine(void *pointer)
{
	t_philo	*philo;

	philo = pointer;
	while (1)
	{
		if (is_someone_dead(philo))
			break ;
		philo_think(philo);
		if (is_someone_dead(philo))
			break ;
		philo_eat(philo);
		if (is_someone_dead(philo))
			break ;
		philo_sleep(philo);
	}
	return (NULL);
}
