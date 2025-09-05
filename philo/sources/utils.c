/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sources utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 18:36:05 by rceschel          #+#    #+#             */
/*   Updated: 2025/09/05 18:39:37 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000UL) + (tv.tv_usec / 1000UL));
}
