/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 18:36:05 by rceschel          #+#    #+#             */
/*   Updated: 2025/09/17 12:31:29 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Lock the writing semaphore and print the log with timestamp
inline void	print_message(t_time time, t_philo *philo, char *message)
{
	sem_wait(philo->write_sem);
	printf("%lu %i %s\n", time, philo->id, message);
	sem_post(philo->write_sem);
}

// Custom usleep implementation to avoid busy waiting
inline int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

// Write function that calculates string length automatically
inline void	ft_write(int fd, char *str)
{
	int	len;

	if (!str)
		return ;
	len = 0;
	while (str[len] != '\0')
		len++;
	write(fd, str, len);
}

// Return current timestamp in milliseconds
inline t_time	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000UL) + (tv.tv_usec / 1000UL));
}
