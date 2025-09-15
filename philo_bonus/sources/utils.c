/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 18:36:05 by rceschel          #+#    #+#             */
/*   Updated: 2025/09/15 16:33:12 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/*
// Lock the writing mutex and print the log followed by a new line
void	print_message(t_time time, t_philo *philo, char *message)
{
	pthread_mutex_lock(philo->write_lock);
	if (!is_someone_dead(philo))
		printf("%lu %i %s\n", time, philo->id, message);
	pthread_mutex_unlock(philo->write_lock);
}

// Return the value of dead_flag
int	is_someone_dead(t_philo *philos)
{
	int	dead;

	pthread_mutex_lock(philos->dead_lock);
	dead = *philos->dead;
	pthread_mutex_unlock(philos->dead_lock);
	return (dead);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}
*/

// write() which calculate the string len
void	ft_write(int fd, char *str)
{
	int	len;

	if (!str)
		return ;
	len = 0;
	while (str[len] != '\0')
		len++;
	write(fd, str, len);
}

// Return current timespamt in usec
t_time	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000UL) + (tv.tv_usec / 1000UL));
}
