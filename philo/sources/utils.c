/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 18:36:05 by rceschel          #+#    #+#             */
/*   Updated: 2025/09/10 18:29:29 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Lock the writing mutex and print time, philo->id and the given message
// followed by a new line
void	print_message(unsigned long time, t_philo *philo, char *message)
{
		pthread_mutex_lock(philo->write_lock);
		printf("%lu %i %s\n", time, philo->id, message);
		pthread_mutex_unlock(philo->write_lock);
}

// Simply the write function but with an argument less
// The passed string needs to be null-terminated
void	ft_write(int fd, char *str)
{
	int	len;

	if(!str)
		return;
	len = 0;
	while(str[len] != '\0')
		len++;
	write(fd, str, len);
}

//void	clean_resources(char *msg, t_program *program, pthread_mutex_t *forks)
//{
//	int	i;
//
//
//	pthread_mutex_lock(&program->write_lock);
//	ft_write(2, msg);
//	ft_write(2, "\n");
//	pthread_mutex_unlock(&program->write_lock);
//	pthread_mutex_destroy(&program->write_lock);
//	pthread_mutex_destroy(&program->meal_lock);
//	pthread_mutex_destroy(&program->dead_lock);
//	i = 0 - 1;
//	while (++i < program->philos->num_of_philos)
//		pthread_mutex_destroy(&forks[i]);
//	cantalloc_clean();
//}

// Return the value of dead_flag
int	is_someone_dead(t_philo *philos)
{
	int	dead;

	pthread_mutex_lock(philos->dead_lock);
	dead = *philos->dead;
	pthread_mutex_unlock(philos->dead_lock);
	return (dead);
}

// Return current timespamt in usec
t_time	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000UL) + (tv.tv_usec / 1000UL));
}
