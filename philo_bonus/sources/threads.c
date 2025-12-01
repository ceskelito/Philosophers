/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 11:35:03 by rceschel          #+#    #+#             */
/*   Updated: 2025/09/17 12:45:23 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Monitor thread to check if all philosophers have eaten required meals
void	*have_philos_ate(void *param)
{
	t_program	*program;
	int			i;

	program = param;
	i = 0;
	while (i < program->rules[e_num_of_philos])
	{
		sem_wait(program->eat_sem);
		i++;
	}
	i = 0;
	sem_wait(program->write_sem);
	while (i < program->rules[e_num_of_philos])
	{
		if (program->philos_pid[i] > 0)
			kill(program->philos_pid[i], SIGTERM);
		i++;
	}
	sem_post(program->write_sem);
	return (NULL);
}

// Monitor thread to check if philosopher is starving
void	*check_last_meal(void *pointer)
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
			if (sem_trywait(philo->dead_sem) == 0)
			{
				sem_wait(philo->write_sem);
				printf("%lu %i died\n", get_current_time() - philo->start_time,
					philo->id);
				sem_post(philo->write_sem);
				exit(1);
			}
			else
				exit(1);
		}
		usleep(500);
	}
	return (NULL);
}
